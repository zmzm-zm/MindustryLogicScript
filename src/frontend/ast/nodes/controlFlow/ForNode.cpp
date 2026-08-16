#include <algorithm>
#include <frontend/ast/nodes/controlFlow/ForNode.hpp>

ForNode::ForNode(std::unique_ptr<VariableNode> initialization,
    std::unique_ptr<ConditionNode> condition,
    std::unique_ptr<VariableNode> expression,
    std::unique_ptr<AstNode> body,
    std::size_t line)
: ControlFlow(std::move(condition), std::move(body), line),
initialization_(std::move(initialization)),
expression_(std::move(expression)) {}

std::string ForNode::toString() {
    // Expand for(init; cond; incr) body into logic code.
    // Layout:
    //   (init statement)
    //   (cond evaluation)                        -> BOOLEAN0_
    //   jump $ENDLINE equal BOOLEAN0_ true  : $SELFLINE
    //   (body)
    //   (incr statement)
    //   jump $HEADLINE always
    //   print "END"                             : $ENDLINE
    std::string initStr = initialization_->toString();

    std::string incrStr = expression_->toString();
    int incrLine = std::ranges::count(incrStr, '\n');

    std::string body;
    for (auto& each : body_->children_) {
        body += each->statement_->toString();
    }
    int bodyLine = std::ranges::count(body, '\n');

    int conditionLine = std::ranges::count(conditionStr_, '\n');

    // selfLine_ points at the line of the jump instruction.
    // init sits right before cond; after the body we jump back to cond's first line (to re-run cond).
    int headLine = selfLine_ - conditionLine - 1;
    // After the body + incr we emit jump HEADLINE, then print "END".
    int endLine  = selfLine_ + bodyLine + incrLine + 1;

    return initStr
            + conditionStr_
            + "jump " + std::to_string(endLine) + " equal BOOLEAN0_ true\n"
            + body
            + incrStr
            + "jump " + std::to_string(headLine) + " always\n"
            + "print \"END\"\n";
}
