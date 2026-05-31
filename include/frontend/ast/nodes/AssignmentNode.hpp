#pragma once
#include <string>
#include <frontend/ast/nodes/StatementNode.hpp>


class AssignmentNode : public StatementNode {
public:
    AssignmentNode(const std::string& variable, const std::string& value);
    std::string toString() override;
    const std::string& getVariable() const;
    const std::string& getValue() const;
private:
    std::string variable_ = "^v^";
    std::string value_ = "^v^";
};
