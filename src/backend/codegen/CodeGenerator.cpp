#include <backend/codegen/CodeGenerator.hpp>
std::string CodeGenerator::generate(const AstNode* node) {
	const auto& statement = node->statement_;
	std::string selfCode = "";
	std::string childrenCode = "";
	if (!(node->statement_ == nullptr))  selfCode = statement->toString();
	for(const auto* each: node->children_) {
		childrenCode += generate(each);
	}
	return selfCode + childrenCode;
}
