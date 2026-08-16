#pragma once
#include <filesystem>
#include <fstream>
#include <string>
namespace fs = std::filesystem;

/**
 * @defgroup Writer Writer
 * @ingroup Backend
 * @brief Writes generated logic code to an output file.
 */

/** @ingroup Writer
 *  @brief Writes generated logic code to an output file.
 */
class Writer {
public:
    /**
     * @brief Opens the target output file.
     * @param fileName Path of the file to write (throws if it cannot be opened).
     */
    explicit Writer(const std::string& fileName);

    /**
     * @brief Appends the given code to the target file.
     * @param code The logic code to write.
     */
    void write(const std::string& code);

private:
    std::ofstream targetFile_; ///< Output file stream.
};