#pragma once
#include <string>
#include <frontend/ast/nodes/AstNode.hpp>

/**
 * @defgroup Backend Backend
 * @ingroup Core
 * @brief Output-side modules: code generation, logging and file writing.
 */

/**
 * @defgroup CodeGen Code Generation
 * @ingroup Backend
 * @brief Generates Mindustry logic text from the parsed AST.
 */

/** @ingroup CodeGen
 *  @brief Generates Mindustry logic text from the parsed AST.
 */
class CodeGenerator {
public:
    /**
     * @brief Recursively serializes an AST node and its children to logic code.
     * @param node The root AST node (nullable).
     * @return The generated logic code as a string.
     */
    static std::string generate(const AstNode* node);
};