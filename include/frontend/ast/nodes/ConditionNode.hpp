#pragma once
#include <frontend/ast/nodes/ExpressionNode.hpp>
class ConditionNode final: public ExpressionNode {
public:
    ConditionNode(const std::string& name,
        std::unique_ptr<ExpressionNode> left = nullptr,
        std::string value = "^v^",
        std::unique_ptr<ExpressionNode> right = nullptr);
    std::string toString() override;
    void setNum(unsigned short num) noexcept;
    unsigned short getNum(unsigned short &num) const noexcept;
private:
    unsigned short num_ = 0;
};
