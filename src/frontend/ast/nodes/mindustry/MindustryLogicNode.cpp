#include <frontend/ast/nodes/mindustry/MindustryLogicNode.hpp>
MindustryLogicNode::MindustryLogicNode(std::string_view logic)
: logic_(logic) {}

std::string MindustryLogicNode::toString() {
    return logic_;
}
