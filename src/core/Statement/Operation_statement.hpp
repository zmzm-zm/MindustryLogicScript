#pragma once
#include <string>
#include <memory>
#include "Statement.hpp"


class Operation_statement : public Statement {
public:
    Operation_statement(const std::string& left,
    	std::string operator__,
    	std::unique_ptr<Operation_statement> right);
    std::string to_string() override;
    const std::string& get_left() const;
    const std::unique_ptr<Operation_statement>& get_right() const;
    const std::string& get_operator() const;
private:
    std::string left_ = "^v^";
    std::string operator_ = "^v^";
    std::string tmp_ = "";
    std::unique_ptr<Operation_statement> right_ = nullptr;
};