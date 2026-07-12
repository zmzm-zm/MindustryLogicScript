#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <frontend/ast/nodes/ConditionNode.hpp>
#include <frontend/lexer/Token.hpp>
#include <frontend/lexer/Tokenizer.hpp>
#include <frontend/parser/Parser.hpp>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/variable/InitializationNode.hpp>
#include <frontend/ast/nodes/OperationNode.hpp>
#include <frontend/ast/nodes/variable/AssignmentNode.hpp>
#include <frontend/ast/nodes/variable/DeclarationNode.hpp>
#include <backend/logger/Logger.hpp>
#include <common/LineCounter.hpp>
#include <frontend/ast/nodes/AstNode.hpp>
#include <frontend/ast/nodes/controlFlow/IfNode.hpp>

Parser::Parser() {}
Parser::~Parser() {}
void Parser::setRoot(std::unique_ptr<AstNode> root) {
	rootNodes_.push(std::move(root));
}
std::unique_ptr<AstNode> Parser::getRoot() {
	return std::move(rootNodes_.top()); // 返回最终结果时，栈内只剩一个根节点
}
void Parser::process() {
	auto currentToken = tokenizer_->peek();
	while(currentToken.type_ != Token::Type::EOF_
		&& currentToken.value_ != "}") {
		switch (currentToken.type_) {
		case Token::Type::KEYWORD:
			if (currentToken.value_ == "var") variableDeclaration();
			if (currentToken.value_ == "if") If();
			break;
		case Token::Type::IDENT:
			if (currentToken.value_.find("(") == std::string::npos) variableAssignment();
			break;
		default:
			throw std::runtime_error("Unexpected token type");
		}
		currentToken = tokenizer_->peek();
	}
}
void Parser::setTokenizer(Tokenizer& tokenizer) {
    tokenizer_ = &tokenizer;
}
std::unique_ptr<StatementNode> Parser::parseInitialization() const {
    tokenizer_->pass();
    auto variable = tokenizer_->nextToken().value_;
    tokenizer_->pass();
	auto linesBefor = LineCounter::getLineCount();
    auto exprNode = parseOperation(variable);
	if (LineCounter::getLineCount() - linesBefor != 1) {
		LineCounter::increment();
	}
    return std::make_unique<InitializationNode>(variable, std::move(exprNode));
}
std::unique_ptr<StatementNode> Parser::parseAssignment() const {
	auto variable = tokenizer_->nextToken().value_;
	tokenizer_->pass();
	auto exprNode = parseOperation(variable);
	return std::make_unique<AssignmentNode>(variable, std::move(exprNode));
}
std::unique_ptr<OperationNode> Parser::parseOperation(
    const std::string name,
    std::size_t index) const {
    std::vector<std::unique_ptr<OperationNode>> output;
    std::vector<Token> operators;
    std::string currentName = name;
    std::size_t currentIndex = index;
    auto makeNodeName = [&]() -> std::string {
    	LineCounter::increment();
        return currentName + std::to_string(currentIndex++) + "_";
    };
    while (true) {
        Token tok = tokenizer_->peek();
        if (tok.type_ == Token::Type::NUMBER || tok.type_ == Token::Type::IDENT) {
            tokenizer_->pass();
            output.push_back(std::make_unique<OperationNode>(
                makeNodeName(), nullptr, tok.value_, nullptr
            ));
        }
        else if (tok.type_ == Token::Type::OPERATOR) {
		    if (tok.value_ == ";") {
		    	tokenizer_->pass();
		        break;
		    }
		    tokenizer_->pass();
		    OperatorType currOp = Tokenizer::analyzeOperator(tok.value_);
		    while (!operators.empty()) {
		        Token top = operators.back();
		        if (top.type_ != Token::Type::OPERATOR) break;
		        OperatorType topOp = Tokenizer::analyzeOperator(top.value_);
		        if ((int)topOp >= (int)currOp) {
		            if (output.size() < 2) {
		                throw std::runtime_error("Invalid Operation: not enough operands for operator " + top.value_);
		            }
		            operators.pop_back();
		            auto right = std::move(output.back());
		            output.pop_back();
		            auto left = std::move(output.back());
		            output.pop_back();
		            output.push_back(std::make_unique<OperationNode>(
		                makeNodeName(), std::move(left), top.value_, std::move(right)
		            ));
		        } else {
		            break;
		        }
		    }
		    operators.push_back(tok);
		}
        else if (tok.type_ == Token::Type::END
        	|| tok.type_ == Token::Type::EOF_
        	|| tok.value_ == "}") {
            break;
        }
        else {
            tokenizer_->pass();
        }
    }
    while (!operators.empty()) {
        Token op = operators.back();
        if (output.size() < 2) {
            throw std::runtime_error("Invalid Operation: not enough operands for operator " + op.value_);
        }
        operators.pop_back();
        auto right = std::move(output.back());
        output.pop_back();
        auto left = std::move(output.back());
        output.pop_back();
        output.push_back(std::make_unique<OperationNode>(
            makeNodeName(), std::move(left), op.value_, std::move(right)
        ));
    	LineCounter::decrement();
    }
    if (output.size() != 1) {
        throw std::runtime_error("Invalid Operation: final stack size is " +
                                  std::to_string(output.size()));
    }
    return std::move(output[0]);
}
std::unique_ptr<ConditionNode> Parser::parseCondition() const {
    // 收集 tokens
    std::vector<std::string> operators;
    std::vector<std::string> logics;
    std::vector<std::string> idents;
    auto nextToken = tokenizer_->nextToken();
    while (nextToken.value_ != ")") {
        if (nextToken.type_ == Token::Type::OPERATOR) {
            if (nextToken.value_ == "&&" || nextToken.value_ == "||") {
                logics.push_back(nextToken.value_);
            } else {
                operators.push_back(nextToken.value_);
            }
        } else if (nextToken.type_ == Token::Type::IDENT ||
                   nextToken.type_ == Token::Type::NUMBER) {
            idents.push_back(nextToken.value_);
        }
        nextToken = tokenizer_->nextToken();
    }

    // 验证输入合法性
    if (idents.empty()) {
        Logger::error("Condition has no operands");
        return std::make_unique<ConditionNode>("NA", nullptr, "false", nullptr);
    }
    uint8_t unitNum = operators.size();
    // 简单情况：没有运算符，直接返回布尔变量
    if (unitNum == 0) {
        return std::make_unique<ConditionNode>(
            "NA",
            nullptr,
            idents[0],
            nullptr
        );
    }
    // 构建操作数节点（叶子节点）
    std::vector<std::unique_ptr<ConditionNode>> operands;
    for (const auto& ident : idents) {
        operands.emplace_back(
            std::make_unique<ConditionNode>(
                "NA",
                nullptr,
                ident,
                nullptr
            )
        );
    }
    // 构建比较单元 (comparison units)
    // 例如: a < b, c == d, e > f
    std::vector<std::unique_ptr<ConditionNode>> comparisons;
    for (uint8_t i = 0; i < unitNum; ++i) {
        // 注意：每个比较单元需要2个操作数
        size_t leftIdx = i * 2;
        size_t rightIdx = i * 2 + 1;
        if (rightIdx >= operands.size()) {
            Logger::error("Not enough operands for comparison");
            break;
        }
        // 从 operands 中取出并转移所有权
        auto left = std::move(operands[leftIdx]);
        auto right = std::move(operands[rightIdx]);
        comparisons.emplace_back(
            std::make_unique<ConditionNode>(
                "NA",
                std::move(left),
                operators[i],
                std::move(right)
            )
        );
    }
    // 清空 operands 所有元素已被 move，变为 nullptr
    operands.clear();
    // 如果只有一个比较单元，直接返回
    if (comparisons.size() == 1) {
        return std::move(comparisons[0]);
    }
    // 如果有多个比较单元，用逻辑运算符连接
    // 例如: (a < b) && (c == d) || (e > f)
    if (logics.empty()) {
        Logger::error("Multiple comparisons but no logical operators");
        // 使用 && 作为默认
        logics.push_back("&&");
    }
    // 构建组合树：从左到右关联
    std::unique_ptr<ConditionNode> result = std::move(comparisons[0]);
    for (size_t i = 1; i < comparisons.size(); ++i) {
        size_t logicIdx = i - 1;
        if (logicIdx >= logics.size()) {
            Logger::error("Not enough logical operators");
            break;
        }
        result = std::make_unique<ConditionNode>(
            "NA",
            std::move(result),
            logics[logicIdx],
            std::move(comparisons[i])
        );
    }
    comparisons.clear();
    return result;
}
std::unique_ptr<StatementNode> Parser::parseDeclaration() const {
	tokenizer_->pass();
	auto var = tokenizer_->nextToken().value_;
	tokenizer_->pass();
	LineCounter::increment();
	return std::make_unique<DeclarationNode>(var);
}
std::unique_ptr<ControlFlow> Parser::parseIf() {
	tokenizer_->pass(); // if
	tokenizer_->pass(); // (
	auto condition = parseCondition();
	std::string conditionStr = condition->toString();
	int conditionLine = std::ranges::count(conditionStr, '\n');
	for (uint8_t i = 0; i < conditionLine; ++i) LineCounter::increment();
	tokenizer_->pass(); // {
	rootNodes_.push(std::make_unique<AstNode>());
	LineCounter::increment();
	auto cureentLine = LineCounter::getLineCount();
	process();
	LineCounter::increment();
	tokenizer_->pass(); // }
	auto node = std::make_unique<IfNode>(std::move(condition), std::move(rootNodes_.top()), cureentLine);
	rootNodes_.pop();
	return std::move(node);
}
void Parser::variableDeclaration() {
	auto var = tokenizer_->peek(2).value_;
	auto c = tokenizer_->peek(3).value_;
	/* 等待语法检查器统一检查
	if (c != "=" && c != ";") Logger::error("expect \"=\" or \";\"");
	 auto it = std::ranges::find(variables_, var);
	if (it != variables_.end()) {
		Logger::error("\" " + var + "\" has been declared");
	}
	 variables_.emplace_back(var);
	*/
	std::unique_ptr<StatementNode> node;
	if(c == ";") node = parseDeclaration();
	else node = parseInitialization();
	rootNodes_.top()->children_.emplace_back(
		new AstNode(std::move(node))
	);
}
void Parser::variableAssignment() {
	auto var = tokenizer_->peek().value_;
	auto c = tokenizer_->peek(2).value_;
	// 等待语法检查器统一检查
	/*
	if (c != "=") Logger::error("expect \"=\"");
	auto it = std::ranges::find(variables_, var);
	if (it == variables_.end()) {
		Logger::error("\" " + var + "\" has not been declared");
	}
	*/
	auto node = parseAssignment();
	rootNodes_.top()->children_.emplace_back(
		new AstNode(std::move(node))
	);
}
void Parser::If() {
	auto ifNode = parseIf();
	rootNodes_.top()->children_.emplace_back(
		new AstNode(std::move(ifNode))
	);
}