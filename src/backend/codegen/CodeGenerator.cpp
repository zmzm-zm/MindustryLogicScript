#include <backend/codegen/CodeGenerator.hpp>
std::string CodeGenerator::generate(const AstNode* node) {
	const auto& statement = node->statement_;
	std::string selfCode = "";
	std::string childrenCode = "";
	if (!(node->statement_ == nullptr)) {
		switch (statement->getType()) {
			case StatementType::ASSIGNMENT:
				selfCode = statement->toString();
				break;
			case StatementType::OPERATION:
				selfCode = statement->toString();
				break;
		}
	}
	for(auto* each: node->children_) {
		childrenCode += generate(each);
	}
	return selfCode + childrenCode;
}