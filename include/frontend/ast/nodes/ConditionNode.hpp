#pragma once
#include <vector>
#include <string>
#include <memory>
#include <frontend/ast/nodes/ExpressionNode.hpp>

class ConditionNode final : public ExpressionNode {
public:
    ConditionNode(const std::string& name,
                  std::unique_ptr<ExpressionNode> left = nullptr,
                  std::string value = "^v^",
                  std::unique_ptr<ExpressionNode> right = nullptr);

    std::string toString() override;

    void setNum(unsigned short num) noexcept;
    unsigned short getNum(unsigned short &num) const noexcept;

private:
    enum class LogicOperator {
        UNKNOWN = -1,
        NON,
        OR,
        AND,
    };

    struct Unit {
        Unit(std::string content, LogicOperator op);
        std::string content_;
        LogicOperator operator_;
    };

    std::string getOpStr(std::string_view str);
    LogicOperator getLogicOp(std::string_view str);

    // 新方法：将表达式树展平为线性 Unit 序列
    std::vector<Unit> flatten(ExpressionNode* node);

    std::vector<Unit> units_;   // 存储展平后的比较单元
    // 已移除：std::stack<std::string> ops_;
};