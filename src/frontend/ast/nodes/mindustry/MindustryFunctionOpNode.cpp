#include <frontend/ast/nodes/mindustry/MindustryFunctionOpNode.hpp>
MindustryFunctionOpNode::MindustryFunctionOpNode(std::string param1, std::string param2, std::string result)
: params_{std::move(param1), std::move(param2)}, result_(std::move(result)) {}