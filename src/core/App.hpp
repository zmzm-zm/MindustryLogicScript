#pragma once
#include <string>
#include <vector>
class App {
public:
	using file_list = std::vector<std::string>;
	  void run(int argc, char** argv);
private:
	void set_source_files(int argc, char** argv);
	file_list files_;
};