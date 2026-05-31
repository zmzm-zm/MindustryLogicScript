#pragma once
#include <string>
enum class StatementType {
    ASSIGNMENT,
    IF,
    LOOP,
    OPERATION,
    UNDEFINED,
};
enum class OperatorType {
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Undefined,
};
class StatementNode {
public:
	StatementType getType();
	virtual std::string toString();
protected:
    StatementType type_ = StatementType::UNDEFINED;
};
