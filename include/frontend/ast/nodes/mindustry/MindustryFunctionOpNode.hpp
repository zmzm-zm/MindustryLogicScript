#pragma once
#include <frontend/ast/nodes/StatementNode.hpp>
class MindustryFunctionOpNode: public StatementNode {
public:
    MindustryFunctionOpNode(std::string param1 = "null", std::string param2 = "null", std::string result = "null");
protected:
    // 截止159.3 所有OP内类函数的运算最多只有两个形参 使用时多余的位置会填充"null"
    std::string params_[2] = {};
    std::string result_ = "null";
};
