#pragma once
#include "ControlFlow.hpp"
#include <frontend/ast/nodes/variable/VariableNode.hpp>

/** @ingroup ControlFlow
 *  @brief A for loop construct (initialization; condition; increment) with a body.
 */
class ForNode final: public ControlFlow {
public:
    /**
     * @brief Constructs a for node.
     * @param initialization The init statement executed once before the loop.
     * @param condition      The loop condition checked each iteration.
     * @param expression     The update statement executed after each iteration.
     * @param body           The loop body.
     * @param line           Line number of the first jump instruction.
     */
    ForNode(std::unique_ptr<VariableNode> initialization,
        std::unique_ptr<ConditionNode> condition,
        std::unique_ptr<VariableNode> expression,
        std::unique_ptr<AstNode> body,
        std::size_t line);

    /** @brief Serializes the for loop to logic code. */
    std::string toString() override;

private:
    std::unique_ptr<VariableNode> initialization_; ///< Init statement.
    std::unique_ptr<VariableNode> expression_;     ///< Update statement.
};
