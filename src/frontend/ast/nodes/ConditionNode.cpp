#include <frontend/ast/nodes/ConditionNode.hpp>
#include <backend/logger/Logger.hpp>
#include <sstream>
#include <vector>

ConditionNode::ConditionNode(
    const std::string& name,
    std::unique_ptr<ExpressionNode> left,
    std::string value,
    std::unique_ptr<ExpressionNode> right)
    : ExpressionNode(name, std::move(left), value, std::move(right)) {}
ConditionNode::Unit::Unit(std::string content, LogicOperator op)
    : content_(std::move(content)), operator_(op) {}
std::string ConditionNode::getOpStr(const std::string_view str) {
    if (str == "<")  return "greaterThanEq";
    if (str == "<=") return "greaterThan";
    if (str == ">")  return "lessThanEq";
    if (str == ">=") return "lessThan";
    if (str == "==") return "notEqual";
    if (str == "===")return "notEqual";
    if (str == "!=") return "equal";
    if (str == "true") return "always";
    Logger::error("Unknown operator: {}", std::string(str));
    return "Unknown operator: " + std::string(str);
}
ConditionNode::LogicOperator ConditionNode::getLogicOp(std::string_view str) {
    if (str == "&&") return LogicOperator::AND;
    if (str == "||") return LogicOperator::OR;
    Logger::error("Unknown operator: {}", std::string(str));
    return LogicOperator::UNKNOWN;
}
std::vector<ConditionNode::Unit> ConditionNode::flatten(ExpressionNode* node) {
    if (!node) return {};
    const auto& val = node->getValue();
    // 比较运算节点
    if (val != "&&" && val != "||") {
        std::string content = "op " + getOpStr(val)
                            + " {} "
                            + node->getLeft()->getValue()
                            + " " + node->getRight()->getValue();
        return { Unit(std::move(content), LogicOperator::AND) };
    }

    // 逻辑运算节点
    LogicOperator curOp = getLogicOp(val);

    // 翻转逻辑连接词
    if (curOp == LogicOperator::AND)
        curOp = LogicOperator::OR;
    else if (curOp == LogicOperator::OR)
        curOp = LogicOperator::AND;

    auto leftUnits  = flatten(node->getLeft());
    auto rightUnits = flatten(node->getRight());

    if (leftUnits.empty()) return rightUnits;
    if (rightUnits.empty()) return leftUnits;

    // 连接左右序列：左侧最后一个单元的 operator_ 设为当前逻辑运算符
    leftUnits.back().operator_ = curOp;

    // 合并右侧序列
    leftUnits.insert(leftUnits.end(),
                     std::make_move_iterator(rightUnits.begin()),
                     std::make_move_iterator(rightUnits.end()));
    return leftUnits;
}
std::string ConditionNode::toString() {
    if (!left_ && !right_) {
        return "op or BOOLEAN1_ " + value_ + " false\n" +
                "op notEqual BOOLEAN0_ true BOOLEAN1_\n";
    }

    units_ = flatten(this);
    if (units_.empty()) return "";

    std::ostringstream out;
    std::vector<std::string> boolNames;
    int counter = 1;

    // 1. 生成所有比较指令
    for (auto& unit : units_) {
        std::string bName = "BOOLEAN" + std::to_string(counter) + "_";
        boolNames.push_back(bName);
        size_t pos = unit.content_.find("{}");
        if (pos != std::string::npos) {
            unit.content_.replace(pos, 2, bName);
        }
        out << unit.content_ << "\n";
        ++counter;
    }

    // 2. 按 OR 分组，段内 AND 归并
    std::vector<std::string> orSegments;
    std::vector<std::string> andStack;

    for (size_t i = 0; i < units_.size(); ++i) {
        andStack.push_back(boolNames[i]);

        if (i == units_.size() - 1 || units_[i].operator_ == LogicOperator::OR) {
            std::string segResult;
            if (andStack.size() == 1) {
                segResult = andStack[0];
            } else {
                std::string left = andStack[0];
                for (size_t j = 1; j < andStack.size(); ++j) {
                    std::string newName = "BOOLEAN" + std::to_string(counter) + "_";
                    out << "op and " << newName << " " << left << " " << andStack[j] << "\n";
                    left = newName;
                    ++counter;
                }
                segResult = left;
            }
            orSegments.push_back(segResult);
            andStack.clear();
        }
    }

    // 3. OR 归并
    if (orSegments.size() == 1) {
        // 单个条件/单个AND段：直接赋给 BOOLEAN0_
        out << "op or BOOLEAN0_ " << orSegments[0] << " " << orSegments[0] << "\n";
    } else {
        std::string left = orSegments[0];
        for (size_t i = 1; i < orSegments.size(); ++i) {
            std::string newName;
            if (i == orSegments.size() - 1) {
                newName = "BOOLEAN0_";
            } else {
                newName = "BOOLEAN" + std::to_string(counter) + "_";
                ++counter;
            }
            out << "op or " << newName << " " << left << " " << orSegments[i] << "\n";
            left = newName;
        }
    }

    return out.str();
}