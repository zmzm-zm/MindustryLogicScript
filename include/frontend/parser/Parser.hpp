#pragma once
#include <memory>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/OperationNode.hpp>
#include <frontend/ast/nodes/AssignmentNode.hpp>
#include <frontend/lexer/Token.hpp>
#include <frontend/lexer/Tokenizer.hpp>


class Parser {
public:
    void setTokenizer(Tokenizer& tokenizer);
    std::unique_ptr<AssignmentNode> parseAssignment() const;
    std::unique_ptr<OperationNode> parseExpression() const;
private:
    Tokenizer* tokenizer_ = nullptr;
};
