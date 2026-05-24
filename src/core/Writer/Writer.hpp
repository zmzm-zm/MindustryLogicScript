#pragma once
#include <filesystem>
#include <fstream>
#include <string>
namespace fs = std::filesystem;
class Writer {
public:
	Writer(std::string file_name);
	void write(const std::string& code);
private:
	std::ofstream target_file_;
};