#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <frontend/lexer/Token.hpp>
#include <frontend/lexer/Tokenizer.hpp>
#include <frontend/parser/Parser.hpp>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/variable/InitializationNode.hpp>
#include <frontend/ast/nodes/ExpressionNode.hpp>
#include <frontend/ast/nodes/variable/AssignmentNode.hpp>

void Parser::setTokenizer(Tokenizer& tokenizer) {
    tokenizer_ = &tokenizer;
}
std::unique_ptr<StatementNode> Parser::parseInitialization() const {
    tokenizer_->pass();
    auto variable = tokenizer_->nextToken().value_;
    tokenizer_->pass();
    auto exprNode = parseExpression(variable);
    return std::make_unique<InitializationNode>(variable, std::move(exprNode));
}
std::unique_ptr<StatementNode> Parser::parseAssignment() const {
	auto variable = tokenizer_->nextToken().value_;
	tokenizer_->pass();
	auto exprNode = parseExpression(variable);
	return std::make_unique<AssignmentNode>(variable, std::move(exprNode));
}
ExpressionNode Parser::parseEachExpression() const {
    std::string left = tokenizer_->nextToken().value_;
    std::string operator_ = tokenizer_->nextToken().value_;
    return ExpressionNode("expr", nullptr, left + operator_, nullptr);
}
std::unique_ptr<ExpressionNode> Parser::parseExpression(
    const std::string name,
    std::size_t index) const {
    
    std::vector<std::unique_ptr<ExpressionNode>> output;
    std::vector<Token> operators;
    std::string currentName = name;
    std::size_t currentIndex = index;
    
    auto makeNodeName = [&]() -> std::string {
        return currentName + std::to_string(currentIndex++);
    };
    
    while (true) {
        Token tok = tokenizer_->peek();
        
		std::cerr << "Processing token: " << tok.value_ << " type=" << (int)tok.type_ 
		          << " output.size=" << output.size() 
		          << " operators.size=" << operators.size() << std::endl;
        if (tok.type_ == Token::Type::NUMBER || tok.type_ == Token::Type::IDENT) {
            tokenizer_->pass();
            output.push_back(std::make_unique<ExpressionNode>(
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
		                throw std::runtime_error("Invalid expression: not enough operands for operator " + top.value_);
		            }
		            operators.pop_back();
		            auto right = std::move(output.back());
		            output.pop_back();
		            auto left = std::move(output.back());
		            output.pop_back();
		            output.push_back(std::make_unique<ExpressionNode>(
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
            throw std::runtime_error("Invalid expression: not enough operands for operator " + op.value_);
        }
        operators.pop_back();
        auto right = std::move(output.back());
        output.pop_back();
        auto left = std::move(output.back());
        output.pop_back();
        output.push_back(std::make_unique<ExpressionNode>(
            makeNodeName(), left.release(), op.value_, right.release()
        ));
    }
    
    if (output.size() != 1) {
        throw std::runtime_error("Invalid expression: final stack size is " + 
                                  std::to_string(output.size()));
    }
    
    return std::move(output[0]);
}
