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
    virtual ~StatementNode() = default;
    virtual StatementType getType() const;
    virtual std::string toString() = 0;
protected:
    StatementType type_ = StatementType::UNDEFINED;
};