#include <stdexcept>
#include <string>
#include <backend/writer/Writer.hpp>
Writer::Writer(const std::string& fileName) {
	targetFile_.open(fileName);
	if (!targetFile_.is_open()) {
		throw std::runtime_error("Can not open file: " + fileName);
	}
}
void Writer::write(const std::string& code) {
	targetFile_ << code;
}