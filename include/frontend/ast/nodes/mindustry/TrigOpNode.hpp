#pragma once
#include <frontend/ast/nodes/mindustry/MindustryFunctionOpNode.hpp>

/** @ingroup Mindustry
 *  @brief A trigonometric operation node (sin / cos / tan / asin / acos / atan).
 */
class TrigOpNode final: public MindustryFunctionOpNode {
public:
    /// The kind of trigonometric operation.
    enum class Type {
        TAN,       ///< Tangent.
        ATAN,      ///< Arctangent.
        SIN,       ///< Sine.
        ASIN,      ///< Arcsine.
        COS,       ///< Cosine.
        ACOS,      ///< Arccosine.
        UNDEFINED  ///< Unset / unknown.
    };

    /**
     * @brief Constructs a trigonometric operation node.
     * @param result The result variable name.
     * @param type   The trigonometric operation type.
     * @param param1 The first parameter (angle value).
     * @param param2 The optional second parameter.
     */
    TrigOpNode(std::string result = "null", Type type = Type::UNDEFINED, std::string param1 = "null", std::string param2 = "null");

    /** @brief Serializes the trigonometric operation to logic code. */
    std::string toString() override;

private:
    Type type_ = Type::UNDEFINED; ///< The trigonometric operation type.
};
