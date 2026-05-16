#pragma once
#include <string>
#include "Statement.hpp"


class Assignment_statement : public Statement {
public:
    Assignment_statement(const std::string& variable, const std::string& value);
private:
    std::string variable_ = "^v^";
    std::string value_ = "^v^";
};
