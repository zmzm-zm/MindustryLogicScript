#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>

/** @ingroup Variable
 *  @brief A variable declaration statement (var x;).
 */
class DeclarationNode final: public VariableNode {
public:
    /**
     * @brief Constructs a declaration node.
     * @param variable The name of the declared variable.
     */
    explicit DeclarationNode(std::string variable);

    /** @brief Serializes the declaration to logic code. */
    std::string toString() override;

    /**
     * @brief Returns the variable name.
     * @return The variable name string.
     */
    std::string getVar() const override;
};
