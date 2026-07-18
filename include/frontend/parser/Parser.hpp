#pragma once
#include <frontend/ast/nodes/StatementNode.hpp>
#include <memory>
#include <stack>
#include <string>
#include <frontend/ast/nodes/AstNode.hpp>
#include <spdlog/logger.h>
class AstNode;
class ControlFlow;
class Tokenizer;
class InitializationNode;
class AssignmentNode;
class OperationNode;
class DeclarationNode;
class ConditionNode;
enum class OperatorType;

class Parser {
public:
	Parser();
	~Parser();
	void setRoot(std::unique_ptr<AstNode> root);
	std::unique_ptr<AstNode> getRoot();
	void process();
    void setTokenizer(Tokenizer& tokenizer);
    std::unique_ptr<StatementNode> parseInitialization() const;
	std::unique_ptr<StatementNode> parseAssignment() const;
    std::unique_ptr<OperationNode> parseOperation(
    std::string name = "^v^",
	    std::size_t index = 0) const;
	std::unique_ptr<ConditionNode> parseCondition() const;
	std::unique_ptr<StatementNode> parseDeclaration() const;
	std::unique_ptr<StatementNode> parseMindustryLogic() const;
	std::unique_ptr<ControlFlow> parseIf();
	std::unique_ptr<ControlFlow> parseWhile();
private:
	void variableDeclaration();
	void variableAssignment();
	void mindustryLogic();
	void If();
	void While();
	Tokenizer* tokenizer_ = nullptr;
	std::stack<std::unique_ptr<AstNode>> rootNodes_;
	spdlog::logger* debug_ = nullptr;
};
