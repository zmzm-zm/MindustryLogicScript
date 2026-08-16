#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>

/** @ingroup Variable
 *  @brief A variable initialization statement (var x = value;).
 */
class InitializationNode final: public VariableNode {
public:
    /**
     * @brief Constructs an initialization node.
     * @param variable The variable name.
     * @param value    The expression assigned to the variable.
     */
    InitializationNode(std::string variable, std::unique_ptr<ExpressionNode> value);

    /** @brief Serializes the initialization to logic code. */
    std::string toString() override;
};
