#include <vector>
#include <frontend/lexer/Token.hpp>
#include <frontend/parser/Parser.hpp>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/AssignmentNode.hpp>
#include <frontend/ast/nodes/OperationNode.hpp>

void Parser::setTokenizer(Tokenizer& tokenizer) {
    tokenizer_ = &tokenizer;
}
std::unique_ptr<AssignmentNode> Parser::parseAssignment() const {
	tokenizer_->pass();
    auto variable = tokenizer_->nextToken();
    tokenizer_->pass();
    auto value = tokenizer_->nextToken();
    tokenizer_->pass();
    return std::make_unique<AssignmentNode>(variable.value_, value.value_);
}
std::unique_ptr<OperationNode> Parser::parseExpression() const {
	std::string left = tokenizer_->nextToken().value_;
	std::string operator_ = tokenizer_->nextToken().value_;
	if (operator_ == ";") return std::make_unique<OperationNode>(left, operator_, nullptr);
	// 右节点为下一个表达式
	auto node = std::make_unique<OperationNode>(left, operator_, parseExpression());
	node->sort();
	return node;
}