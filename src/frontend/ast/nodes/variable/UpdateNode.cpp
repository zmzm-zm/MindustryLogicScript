#include <format>
#include <frontend/ast/nodes/variable/UpdateNode.hpp>

UpdateNode::UpdateNode(std::string var, std::string op, std::unique_ptr<ExpressionNode> value)
: op_(op),
VariableNode(var, std::move(value)) {}

UpdateNode::UpdateNode(std::string var, std::string op, std::string ident)
: op_(op), ident_(ident),
VariableNode(var, nullptr) {}

std::string UpdateNode::toString() {
    std::string ident = op_ == "++" || op_ == "--"
                        ? "1"
                        : ident_;
    if (op_ == "++" || op_ == "+=") op_ = "add";
    else if (op_ == "--" || op_ == "-=") op_ = "sub";
    else if (op_ == "*=") op_ = "mul";
    else if (op_ == "/=") op_ = "div";
    else op_ = "unknown or unsupported operator";
    if (!value_)return std::format("op {} {} {} {}\n", op_, variable_, variable_, ident);
    return value_->toString()
        + std::format("op {} {} {} {}\n", op_, variable_, variable_, value_->getName());
}