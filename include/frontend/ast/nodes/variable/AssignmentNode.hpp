#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>

/** @ingroup Variable
 *  @brief A variable assignment statement (x = value;).
 */
class AssignmentNode final: public VariableNode {
public:
    /**
     * @brief Constructs an assignment node.
     * @param variable The variable name.
     * @param value    The expression assigned to the variable.
     */
    AssignmentNode(std::string variable, std::unique_ptr<ExpressionNode> value);

    /** @brief Serializes the assignment to logic code. */
    std::string toString() override;
};
