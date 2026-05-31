#pragma once
#include <string>
#include <memory>
#include <frontend/ast/nodes/StatementNode.hpp>


class OperationNode : public StatementNode {
public:
    OperationNode(const std::string& left,
    	std::string operator__,
    	std::unique_ptr<OperationNode> right);
    std::string toString() override;
    const std::string& getLeft() const;
    const std::unique_ptr<OperationNode>& getRight() const;
    const std::string& getOperator() const;
private:
    std::string left_ = "^v^";
    std::string operator_ = "^v^";
    std::string tmp_ = "";
    std::unique_ptr<OperationNode> right_ = nullptr;
};