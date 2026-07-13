#pragma once
#include <frontend/ast/nodes/StatementNode.hpp>

class MindustryLogicNode final: public StatementNode {
public:
    MindustryLogicNode(std::string_view logic);
    std::string toString() override;
private:
    std::string logic_;
};
