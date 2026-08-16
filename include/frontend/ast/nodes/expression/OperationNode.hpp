#pragma once
#include <frontend/ast/nodes/expression/ExpressionNode.hpp>

/** @ingroup Expression
 *  @brief An arithmetic operation node (e.g. a + b).
 */
class OperationNode final: public ExpressionNode {
public:
    /**
     * @brief Constructs an operation node.
     * @param name  Intermediate variable name.
     * @param left  Left operand.
     * @param value Operator symbol (+, -, *, /, %...).
     * @param right Right operand.
     */
    OperationNode(const std::string& name,
        std::unique_ptr<ExpressionNode> left = nullptr,
        std::string value = "^v^",
        std::unique_ptr<ExpressionNode> right = nullptr);

    /** @brief Serializes the operation tree to logic code. */
    std::string toString() override;

private:
    friend class Parser;
};
