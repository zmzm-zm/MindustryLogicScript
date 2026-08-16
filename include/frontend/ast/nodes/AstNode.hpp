#pragma once
#include <vector>
#include <memory>
#include "frontend/ast/nodes/StatementNode.hpp"

/**
 * @defgroup ASTNodes AST Nodes
 * @ingroup Frontend
 * @brief Abstract syntax tree node types.
 */

/** @ingroup ASTNodes
 *  @brief A generic node of the abstract syntax tree.
 *  @details May hold a statement and any number of child nodes.
 */
class AstNode {
public:
    /// @brief Constructs an empty node with no statement.
    AstNode();

    /**
     * @brief Constructs a node wrapping the given statement.
     * @param statementNode The statement this node represents.
     */
    AstNode(std::unique_ptr<StatementNode> statementNode);

    /// The list of child nodes (e.g. the body of a control-flow block).
    std::vector<AstNode*> children_;

    /// The statement this node holds (null for pure container nodes).
    std::unique_ptr<StatementNode> statement_;
};
