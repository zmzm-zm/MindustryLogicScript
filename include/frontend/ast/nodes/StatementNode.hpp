#pragma once
#include <string>

enum class StatementType {
    UNDEFINED,
    ASSIGNMENT,
    OPERATION,
    IF,
    LOOP,
    PRINT
};

class StatementNode {
public:
    virtual std::string toString() = 0;
    virtual ~StatementNode() = default;
};
