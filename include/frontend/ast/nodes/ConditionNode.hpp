#pragma once
#include <frontend/ast/nodes/ExpressionNode.hpp>
// a < b && c < d
class ConditionNode: public ExpressionNode {
public:
    ConditionNode(const std::string& name,
        ExpressionNode* left = nullptr,
        std::string value = "^v^",
        ExpressionNode* right = nullptr);
    std::string toString() override;
    void setNum(unsigned short num) noexcept;
    unsigned short getNum(unsigned short &num) const noexcept;
private:
    unsigned short num_;
};
