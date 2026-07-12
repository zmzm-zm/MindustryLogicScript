#include <algorithm>
#include <backend/logger/Logger.hpp>
#include <common/LineCounter.hpp>
#include <frontend/ast/nodes/controlFlow/IfNode.hpp>
IfNode::IfNode(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body, std::size_t line)
: ControlFlow(std::move(condition), std::move(body), line) {
}
std::string IfNode::toString() {
    std::string body;
    for (auto& each: body_->children_) {
        body += each->statement_->toString();
    }
    int targetLine = selfLine_ +
        std::count(body.begin(), body.end(), '\n');
    return conditionStr_ +
            "jump " + std::to_string(targetLine) + " equal BOOLEAN0_ true\n"
            + body
            + "print \"END\"\n";
}