#include <format>
#include <frontend/ast/nodes/mindustry/TrigOpNode.hpp>
TrigOpNode::TrigOpNode(std::string result, Type type, std::string param1, std::string param2)
: MindustryFunctionOpNode(std::move(param1), std::move(param2), std::move(result)), type_(type) {}
std::string TrigOpNode::toString() {
    std::string name;
    switch (type_) {
    case Type::TAN:
        name = "tan";
        break;
    case Type::ATAN:
        name = "atan";
        break;
    case Type::SIN:
        name = "sin";
        break;
    case Type::ASIN:
        name = "asin";
        break;
    case Type::COS:
        name = "cos";
        break;
    case Type::ACOS:
        name = "acos";
        break;
    default:
        name = "unknown";
        break;
    }
    return std::format("op {} {} {}\n", name, result_, params_[0]);
}