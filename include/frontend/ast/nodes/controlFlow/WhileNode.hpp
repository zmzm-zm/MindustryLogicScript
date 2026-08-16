#pragma once
#include <frontend/ast/nodes/controlFlow/ControlFlow.hpp>
/*
 * A while loop guards a body with a condition and repeats until the condition fails.
 * Example input for:
 * var a = 0;
 * while (a < 10) {
 *      a = a + 1;
 * }
 * 0 1 2 3 4 5 6 7 8 9 10
 0* set a 0
 1* op greaterThanEq BOOLEAN1_ a 10
 2* op or BOOLEAN0_ BOOLEAN1_ BOOLEAN1_
 3* jump 6 equal BOOLEAN0_ true
 4* op add a a 1
 5* jump 1 always
 6* print "END"
 *
 * $CONDITION :$HEADLIINE = $WHILELINE - line($CONDITION)
 * jump $ENDLINE equal BOOLEAN0_ true :$WHILELINE
 * $BODY
 * jump $HEADLIINE always
 * print "END" :$ENDLINE = $WHILELINE + line($BODY) + 1
 *
 */

/** @ingroup ControlFlow
 *  @brief A while loop construct.
 */
class WhileNode final: public ControlFlow {
public:
    /**
     * @brief Constructs a while node.
     * @param condition The loop condition.
     * @param body      The loop body.
     * @param line      The source line where the while appears.
     */
    WhileNode(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body, std::size_t line);

    /** @brief Serializes the while loop to logic code. */
    std::string toString() override;
};