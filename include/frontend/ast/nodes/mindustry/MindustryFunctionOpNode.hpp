#pragma once
#include <frontend/ast/nodes/StatementNode.hpp>

/**
 * @defgroup Mindustry Mindustry
 * @ingroup ASTNodes
 * @brief Mindustry-specific node types (raw logic blocks and function ops).
 */

/** @ingroup Mindustry
 *  @brief Base class for Mindustry function operations.
 */
class MindustryFunctionOpNode: public StatementNode {
public:
    /**
     * @brief Constructs a Mindustry function-op node.
     * @param param1 First parameter (defaults to "null").
     * @param param2 Second parameter (defaults to "null").
     * @param result The result variable name (defaults to "null").
     */
    MindustryFunctionOpNode(std::string param1 = "null", std::string param2 = "null", std::string result = "null");

protected:
    /// As of 159.3, every function-like op takes at most two parameters; unused slots are filled with "null".
    std::string params_[2] = {};
    std::string result_ = "null";
};
