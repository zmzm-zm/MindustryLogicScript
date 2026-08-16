#pragma once
#include <memory>
#include <frontend/ast/nodes/AstNode.hpp>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/expression/ConditionNode.hpp>

/**
 * @defgroup ControlFlow Control Flow
 * @ingroup ASTNodes
 * @brief Control-flow constructs (if / while / for).
 */

/** @ingroup ControlFlow
 *  @brief Base class for control-flow constructs (if / while / for...).
 */
class ControlFlow: public StatementNode {
public:
    /**
     * @brief Constructs a control-flow node.
     * @param condition The condition expression.
     * @param body      The body executed when the condition is met.
     * @param line      The source line where this construct appears.
     */
    ControlFlow(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body, std::size_t line);

    /** @brief Serializes the control-flow construct to logic code. */
    std::string toString() override;

protected:
    std::size_t selfLine_ = 0;                          ///< Line number of the first jump instruction.
    std::string conditionStr_ = "";                    ///< Cached serialized condition.
    std::unique_ptr<ConditionNode> condition_;          ///< The condition expression.
    std::unique_ptr<AstNode> body_ = nullptr;           ///< The construct body.
};