#pragma once
#include <string>
#include <memory>
#include <frontend/ast/nodes/StatementNode.hpp>
enum class OperatorType;

class ExpressionNode : public StatementNode {
public:
    ExpressionNode(const std::string& name,
        std::unique_ptr<ExpressionNode> left = nullptr,
        std::string value = "^v^",
        std::unique_ptr<ExpressionNode> right = nullptr);
    
    ~ExpressionNode();
    std::string toString() override;
    ExpressionNode* getLeft() const;
    void setLeft(std::unique_ptr<ExpressionNode> left);
    ExpressionNode* getRight() const;
    void setRight(std::unique_ptr<ExpressionNode> right);
    const std::string& getValue() const;
    OperatorType getOperatorType() const;
    const std::string& getName() const;

protected:
    friend class Parser;
    std::unique_ptr<ExpressionNode> left_ = nullptr;
    std::unique_ptr<ExpressionNode> right_ = nullptr;
    std::string name_ = "nana";
    std::string value_ = "^v^";
    OperatorType operatorType_ = static_cast<OperatorType>(0);
};