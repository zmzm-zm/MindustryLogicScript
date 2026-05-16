#pragma once

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
protected:
    Statement_type type_ = Statement_type::UNDEFINED;
};
