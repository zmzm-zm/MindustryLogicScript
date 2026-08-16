#pragma once
#include <vector>
#include <string>
#include <memory>
#include <frontend/ast/nodes/expression/ExpressionNode.hpp>

/** @ingroup Expression
 *  @brief A boolean condition composed of comparison units joined by logical operators.
 */
class ConditionNode final : public ExpressionNode {
public:
    /**
     * @brief Constructs a condition node.
     * @param name  Intermediate variable name.
     * @param left  Left operand or sub-expression.
     * @param value Comparison / logic operator symbol or literal.
     * @param right Right operand or sub-expression.
     */
    ConditionNode(const std::string& name,
                  std::unique_ptr<ExpressionNode> left = nullptr,
                  std::string value = "^v^",
                  std::unique_ptr<ExpressionNode> right = nullptr);

    /** @brief Serializes the condition to logic code. */
    std::string toString() override;

    /**
     * @brief Sets the node's sequence number.
     * @param num The new number.
     */
    void setNum(unsigned short num) noexcept;

    /**
     * @brief Sets the internal number from the given reference.
     * @param num Reference whose value is copied into the node.
     * @return The value that was set.
     */
    unsigned short getNum(unsigned short &num) const noexcept;

private:
    /// Logical operator used to join comparison units.
    enum class LogicOperator {
        UNKNOWN = -1,
        NON,
        OR,
        AND,
    };

    /// A single flattened comparison unit with its joining logical operator.
    struct Unit {
        Unit(std::string content, LogicOperator op);
        std::string content_;        ///< The comparison operation text.
        LogicOperator operator_;     ///< Logical operator joining the next unit.
    };

    /**
     * @brief Maps a comparison symbol to its Mindustry operation name.
     * @param str The comparison symbol.
     * @return The generated operation name.
     */
    std::string getOpStr(std::string_view str);

    /**
     * @brief Maps a logic symbol to a LogicOperator value.
     * @param str The logic symbol (&& / ||).
     * @return The corresponding LogicOperator.
     */
    LogicOperator getLogicOp(std::string_view str);

    /// Flattens the expression tree into a linear sequence of units.
    std::vector<Unit> flatten(ExpressionNode* node);

    std::vector<Unit> units_;  ///< Storage for the flattened comparison units.
};