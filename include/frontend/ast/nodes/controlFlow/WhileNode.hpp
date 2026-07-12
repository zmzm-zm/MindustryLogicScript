#pragma once
#include <frontend/ast/nodes/controlFlow/ControlFlow.hpp>
/*
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
 * print "END" :$ENDLINE = $WHILELINE + line($BODY) + 2
 *
 */
class WhileNode final: public ControlFlow {
public:
    WhileNode(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body, std::size_t line);
    std::string toString() override;
};