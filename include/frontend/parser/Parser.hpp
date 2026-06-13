#pragma once
#include "frontend/ast/nodes/StatementNode.hpp"
#include <memory>
#include <string>
class Tokenizer;
class InitializationNode;
class AssignmentNode;
class ExpressionNode;
enum class OperatorType;

class Parser {
public:
    void setTokenizer(Tokenizer& tokenizer);
    std::unique_ptr<StatementNode> parseInitialization() const;
	std::unique_ptr<StatementNode> parseAssignment() const;
    std::unique_ptr<ExpressionNode> parseExpression(
	    const std::string name = "^v^",
	    std::size_t index = 0) const;
private:
	ExpressionNode parseEachExpression() const;
    Tokenizer* tokenizer_ = nullptr;
};
