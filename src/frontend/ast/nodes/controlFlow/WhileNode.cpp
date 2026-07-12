#include <algorithm>
#include <frontend/ast/nodes/controlFlow/WhileNode.hpp>
WhileNode::WhileNode(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body, std::size_t line)
: ControlFlow(std::move(condition), std::move(body), line) {}

std::string WhileNode::toString() {
    auto condition = condition_->toString();
    std::string body;
    for (auto& each: body_->children_) {
        body += each->statement_->toString();
    }
    int bodyLine = std::ranges::count(body, '\n');
    int conditionLine = std::ranges::count(condition, '\n');
    int headLine = selfLine_ - conditionLine - 1;
    int endLine =  selfLine_ + bodyLine + 1;
    return conditionStr_
            + "jump " + std::to_string(endLine) + " equal BOOLEAN0_ true\n"
            + body
            + "jump " + std::to_string(headLine) + " always\n"
            + "print \"END\"\n";
}
