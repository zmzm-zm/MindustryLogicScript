#include <backend/codegen/CodeGenerator.hpp>
std::string CodeGenerator::generate(const AstNode* node) {
	if (!node) return "";
	std::string result = "";
	if (node->statement_) {
		result += node->statement_->toString();
	}
	for (const auto* each : node->children_) {
		result += generate(each);
	}
	return result;
}
