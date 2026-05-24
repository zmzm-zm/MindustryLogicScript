#pragma once
#include <string>
#include "Statement.hpp"


class If_statement : public Statement {
public:
    If_statement(const std::string& variable, const std::string& value);
    std::string to_string() const override;
    const std::string& get_variable() const;
    const std::string& get_value() const;
private:
    std::string variable_ = "^v^";
    std::string value_ = "^v^";
};