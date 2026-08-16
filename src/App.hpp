#pragma once
#include <string>
#include <vector>
#include <frontend/lexer/Tokenizer.hpp>
#include <frontend/parser/Parser.hpp>
#include <backend/writer/Writer.hpp>
#include <backend/logger/Logger.hpp>

/**
 * @defgroup Core Core
 * @brief Root module. Backend, Frontend and Common are grouped beneath it.
 */

/** @ingroup Core
 *  @brief Top-level application orchestrating the compile pipeline.
 */
class App {
public:
    /**
     * @brief Constructs the application and initializes the compiler pipeline.
     * @param argc Number of command-line arguments.
     * @param argv Command-line arguments (argv[1] = output name, argv[2..] = source files).
     */
    App(uint8_t argc, char** argv);

    /// @brief Destroys the application.
    ~App();
    using fileList = std::vector<std::string>;

    /** @brief Runs the compilation pipeline and writes the output. */
    void run();

private:
    /**
     * @brief Validates and collects the source files from the command line.
     * @param argc Number of command-line arguments.
     * @param argv Command-line arguments.
     */
    void setSourceFiles(uint8_t argc, char** argv);
    fileList files_;                   ///< List of source file paths.
    Parser parser_;
    Tokenizer tokenizer_;
    Writer writer_;                    ///< The output writer.
    std::vector<std::string> variables_; ///< Declared variable names (unused here).
};
