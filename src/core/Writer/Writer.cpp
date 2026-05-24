#include <stdexcept>
#include <string>
#include "Writer.hpp"
Writer::Writer(std::string file_name) {
	target_file_.open(file_name);
	if (!target_file_.is_open()) {
		throw std::runtime_error("Can not open file: " + file_name);
	}
}
void Writer::write(const std::string& code) {
	target_file_ << code;
}