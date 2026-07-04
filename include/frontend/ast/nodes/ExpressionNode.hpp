#pragma once
#include <string>
#include <frontend/ast/nodes/StatementNode.hpp>
enum class OperatorType;

class ExpressionNode : public StatementNode {
public:
    ExpressionNode(const std::string& name,
        ExpressionNode* left = nullptr,
        std::string value = "^v^",
        ExpressionNode* right = nullptr);
    
    ~ExpressionNode();
    std::string toString() override;
    ExpressionNode* getLeft() const;
    void setLeft(ExpressionNode* left);
    ExpressionNode* getRight() const;
    void setRight(ExpressionNode* right);
    const std::string& getValue() const;
    OperatorType getOperatorType() const;
    const std::string& getName() const;

protected:
    friend class Parser;
    ExpressionNode* left_ = nullptr;
    ExpressionNode* right_ = nullptr;
    std::string name_ = "nana";
    std::string value_ = "^v^";
    OperatorType operatorType_ = static_cast<OperatorType>(0);
};