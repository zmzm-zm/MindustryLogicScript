#pragma once
#include <string>
enum class Statement_type {
    ASSIGNMENT,
    IF,
    LOOP,
    OPERATION,
    UNDEFINED,
};
enum class Operator_type {
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Undefined,
};
class Statement {
public:
	Statement_type get_type();
	virtual std::string to_string();
protected:
    Statement_type type_ = Statement_type::UNDEFINED;
};
