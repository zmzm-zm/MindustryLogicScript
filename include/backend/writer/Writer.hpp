#pragma once
#include <filesystem>
#include <fstream>
#include <string>
namespace fs = std::filesystem;
class Writer {
public:
	Writer(std::string fileName);
	void write(const std::string& code);
private:
	std::ofstream targetFile_;
};