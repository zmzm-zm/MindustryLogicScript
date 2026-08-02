#pragma once
#include <frontend/ast/nodes/mindustry/MindustryFunctionOpNode.hpp>
class TrigOpNode final: public MindustryFunctionOpNode {
public:
    enum class Type {
        TAN,
        ATAN,
        SIN,
        ASIN,
        COS,
        ACOS,
        UNDEFINED
    };
    TrigOpNode( std::string result = "null", Type type = Type::UNDEFINED, std::string param1 = "null", std::string param2 = "null");
    std::string toString() override;
private:
    Type type_ = Type::UNDEFINED;
};
