#pragma once
#include <string>
#include <functional>
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

private:
    friend class Parser;
    static size_t size_;
    std::string name_ = "nana";
    ExpressionNode* left_ = nullptr;
    std::string value_ = "^v^";
    ExpressionNode* right_ = nullptr;
    OperatorType operatorType_ = static_cast<OperatorType>(0);
};