#include "Assignment_statement.hpp"
Assignment_statement::Assignment_statement(const std::string& variable, const std::string& value):
    variable_(variable), value_(value) {
    type_ = Statement_type::ASSIGNMENT;
}
