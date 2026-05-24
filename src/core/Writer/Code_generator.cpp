#include "Code_generator.hpp"
std::string Code_generator::generate(const AST_node* node) {
	const auto& statement = node->statement_;
	std::string self_code = "";
	std::string children_code = "";
	if (!(node->statement_ == nullptr)) {
		switch (statement->get_type()) {
			case Statement_type::ASSIGNMENT:
				self_code = statement->to_string();
				break;
			case Statement_type::OPERATION:
				self_code = statement->to_string();
				break;
		}
	}
	for(auto* each: node->children_) {
		children_code += generate(each);
	}
	return self_code + children_code;
}