#pragma once
#include <string>
#include <memory>
#include <frontend/ast/nodes/StatementNode.hpp>
enum class OperatorType;

/**
 * @defgroup Expression Expression
 * @ingroup ASTNodes
 * @brief Expression node types (operations and conditions).
 */

/** @ingroup Expression
 *  @brief Represents an expression within the AST (base for operations and conditions).
 */
class ExpressionNode : public StatementNode {
public:
    /**
     * @brief Constructs an expression node.
     * @param name  Name of the intermediate variable.
     * @param left  Optional left-hand operand.
     * @param value The operator symbol or literal value.
     * @param right Optional right-hand operand.
     */
    ExpressionNode(const std::string& name,
        std::unique_ptr<ExpressionNode> left = nullptr,
        std::string value = "^v^",
        std::unique_ptr<ExpressionNode> right = nullptr);

    /// @brief Virtual destructor.
    ~ExpressionNode();

    /** @brief Serializes the expression to logic code. */
    std::string toString() override;

    /** @brief Returns the left operand (nullable). @return The left child node. */
    ExpressionNode* getLeft() const;

    /** @brief Sets the left operand. @param left The new left child node. */
    void setLeft(std::unique_ptr<ExpressionNode> left);

    /** @brief Returns the right operand (nullable). @return The right child node. */
    ExpressionNode* getRight() const;

    /** @brief Sets the right operand. @param right The new right child node. */
    void setRight(std::unique_ptr<ExpressionNode> right);

    /** @brief Returns the operator symbol or literal value. @return The stored value string. */
    const std::string& getValue() const;

    /** @brief Returns the parsed operator type of the value. @return The operator type. */
    OperatorType getOperatorType() const;

    /** @brief Returns the generated name of this expression. @return The name string. */
    const std::string& getName() const;

protected:
    friend class Parser;

    std::unique_ptr<ExpressionNode> left_ = nullptr;  ///< Left operand child.
    std::unique_ptr<ExpressionNode> right_ = nullptr; ///< Right operand child.
    std::string name_ = "nana";                      ///< Records the variable name passed in.
    std::string value_ = "^v^";                      ///< Operator symbol or literal.
    OperatorType operatorType_ = static_cast<OperatorType>(0); ///< Parsed operator type.
};