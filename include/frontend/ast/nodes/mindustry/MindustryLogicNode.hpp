#pragma once
#include <frontend/ast/nodes/StatementNode.hpp>

/** @ingroup Mindustry
 *  @brief Represents a raw Mindustry logic block written inline in the source.
 */
class MindustryLogicNode final: public StatementNode {
public:
    /**
     * @brief Constructs a node holding raw Mindustry logic.
     * @param logic The raw logic text.
     */
    MindustryLogicNode(std::string_view logic);

    /** @brief Returns the raw logic text. */
    std::string toString() override;

private:
    std::string logic_;
};
