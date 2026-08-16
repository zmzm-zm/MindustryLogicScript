#pragma once
#include <frontend/ast/nodes/StatementNode.hpp>
#include <memory>
#include <stack>
#include <string>
#include <frontend/ast/nodes/AstNode.hpp>
#include <spdlog/logger.h>
class VariableNode;
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
private:
	std::unique_ptr<VariableNode> parseDeclaration();
	std::unique_ptr<VariableNode> parseInitialization();
	std::unique_ptr<VariableNode> parseAssignment() const;
	std::unique_ptr<OperationNode> parseOperation(
		std::string name = "^v^",
		std::size_t index = 0) const;
	std::unique_ptr<ConditionNode> parseCondition(std::string ending = ")") const;
	std::unique_ptr<StatementNode> parseMindustryLogic() const;
	std::unique_ptr<ControlFlow> parseIf();
	std::unique_ptr<ControlFlow> parseWhile();
	std::unique_ptr<ControlFlow> parseFor();
	std::string parseTrig(std::string resultName, std::string value) const;
	std::unique_ptr<VariableNode> parseIncrementDecrement();
	void variableDeclaration();
	void variableAssignment();
	void mindustryLogic();
	void If();
	void While();
	void For();
	void IncrementDecrement();
	void isVariableDeclared(std::string_view name) const;
	void isVariableUndeclared(std::string_view name) const;
	void addVariable(std::string_view name);
	Tokenizer* tokenizer_ = nullptr;
	std::stack<std::unique_ptr<AstNode>> rootNodes_;
	spdlog::logger* debug_ = nullptr;
	std::vector<std::string> variables_;
};
