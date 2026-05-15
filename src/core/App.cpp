#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "App.hpp"
namespace fs = std::filesystem;
void App::run(int argc, char** argv) {
	try {
		set_source_files(argc, argv);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
void App::set_source_files(int argc, char** argv) {
	for(int i = i; i < argc; ++i) {
		if (!fs::is_regular_file(argv[i])) {
			throw std::runtime_error("Can not find file\"" + std::string(argv[i])) + "\"";
		}
	}
	files_.assign(argv + 1, argv + argc);
}