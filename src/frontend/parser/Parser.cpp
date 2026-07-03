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

void Parser::setTokenizer(Tokenizer& tokenizer) {
    tokenizer_ = &tokenizer;
}
std::unique_ptr<StatementNode> Parser::parseInitialization() const {
    tokenizer_->pass();
    auto variable = tokenizer_->nextToken().value_;
    tokenizer_->pass();
    auto exprNode = parseOperation(variable);
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
        return currentName + std::to_string(currentIndex++) + "_";
    };
    while (true) {
        Token tok = tokenizer_->peek();
        /*
		std::cerr << "Processing token: " << tok.value_ << " type=" << (int)tok.type_
		          << " output.size=" << output.size() 
		          << " operators.size=" << operators.size() << std::endl;
    	*/
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
		                makeNodeName(), left.release(), top.value_, right.release()
		            ));
		        } else {
		            break;
		        }
		    }
		    operators.push_back(tok);
		}
        else if (tok.type_ == Token::Type::END || tok.type_ == Token::Type::EOF_) {
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
            makeNodeName(), left.release(), op.value_, right.release()
        ));
    }
    if (output.size() != 1) {
        throw std::runtime_error("Invalid Operation: final stack size is " + 
                                  std::to_string(output.size()));
    }
    return std::move(output[0]);
}
std::unique_ptr<ConditionNode> Parser::parseCondition() const {
	// 获取 运算符 逻辑运算符 操作对象
	std::vector<std::string> operators;
	std::vector<std::string> logics;
	std::vector<std::string> idents;
	int index = 0;
	auto nextToken = tokenizer_->nextToken();
	while (nextToken.value_ != ")") {
		if (nextToken.type_ == Token::Type::OPERATOR) {
			if (nextToken.value_ == "&&" ||  nextToken.value_ == "||") logics.push_back(nextToken.value_);
			else operators.push_back(nextToken.value_);
		}
		else if (nextToken.type_ == Token::Type::IDENT) idents.push_back(nextToken.value_);
		++index;
		nextToken = tokenizer_->nextToken();
	}
	// 计算有多少个比较单元 比如 a < b 是一个单元
	int unitNum = operators.size();
	// 没有运算时，直接返回变量名 针对if (booleanValue)
	if (unitNum == 0) return std::make_unique<ConditionNode>(
								"NA",
								nullptr,
								idents[0],
								nullptr);
	// 构建 操作数的节点，叶子节点
	std::vector<ConditionNode*> identNodes;
	for (auto & ident : idents) {
		identNodes.emplace_back(
			"NA",
			nullptr,
			ident,
			nullptr);
	}
	// 只有一个单元时 直接返回
	if (unitNum == 1) return std::make_unique<ConditionNode>(
								"NA",
								identNodes[0],
								operators[0],
								identNodes[1]);
	// 把 叶子节点 缀在 每个单元节点的两枝
	// 运算符数量 等于 单元数
	// 叶子数 等于 二倍的单元数
	/* 化简
	 * identNodes[(i + 1) * 2 - 2] = i * 2
	 * identNodes[(i + 1) * 2 - 1] = i * 2 + 1
	 */
	std::vector<ConditionNode*> conditions;
	for (int i = 0; i < unitNum; ++i) {
		conditions.emplace_back(
			"NA",
			identNodes[i * 2],
			operators[i],
			identNodes[i * 2 + 1]);
	}
	// 联系单元节点
	// 先把第一第二个联系起来
	// 随后联系前一个联系节点和后一个单元节点 因此循环次数 - 2
	// 逻辑运算符数 = 单元数 - 1
	std::vector<ConditionNode*> output;
	output.emplace_back(
			"NA",
			conditions[0],
			logics[0],
			conditions[1]);
	for (int i = 2; i < unitNum; ++i) {
		output.emplace_back(
			"NA",
			output[i - 2],
			logics[i - 1],
			conditions[i]);
	}
	return std::make_unique<ConditionNode>(*output[output.size() - 1]);
}


std::unique_ptr<StatementNode> Parser::parseDeclaration() const {
	tokenizer_->pass();
	auto var = tokenizer_->nextToken().value_;
	tokenizer_->pass();
	return std::make_unique<DeclarationNode>(var);
}
