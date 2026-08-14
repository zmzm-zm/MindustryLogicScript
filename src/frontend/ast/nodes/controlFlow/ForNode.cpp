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
    // for(init; cond; incr) body 展开为逻辑码
    // 结构:
    //   (init 语句)
    //   (cond 计算)                         -> BOOLEAN0_
    //   jump $ENDLINE equal BOOLEAN0_ true  : $SELFLINE
    //   (body)
    //   (incr 语句)
    //   jump $HEADLINE always
    //   print "END"                         : $ENDLINE
    std::string initStr = initialization_->toString();
    int initLine = std::ranges::count(initStr, '\n');

    std::string incrStr = expression_->toString();
    int incrLine = std::ranges::count(incrStr, '\n');

    std::string body;
    for (auto& each : body_->children_) {
        body += each->statement_->toString();
    }
    int bodyLine = std::ranges::count(body, '\n');

    int conditionLine = std::ranges::count(conditionStr_, '\n');

    // selfLine_ 指向 jump 指令所在行。
    // init 紧挨在 cond 之前; 循环体结束后需要跳回 init 第一行(重跑 init+cond)。
    int headLine = selfLine_ - conditionLine - 1;
    // 循环体 + incr 之后是 jump HEADLINE, 再之后是 print "END"。
    // ENDLINE = selfLine_ + bodyLine + incrLine + 2
    int endLine  = selfLine_ + bodyLine + incrLine + 1;

    return initStr
            + conditionStr_
            + "jump " + std::to_string(endLine) + " equal BOOLEAN0_ true\n"
            + body
            + incrStr
            + "jump " + std::to_string(headLine) + " always\n"
            + "print \"END\"\n";
}
