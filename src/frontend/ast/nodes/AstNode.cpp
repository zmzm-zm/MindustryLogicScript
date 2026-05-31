#include <frontend/ast/nodes/AstNode.hpp>
AstNode::AstNode(std::unique_ptr<StatementNode> statement) {
	statement_ = std::move(statement);
}