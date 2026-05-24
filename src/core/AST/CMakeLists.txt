add_library(Ast SHARED)
target_sources(Ast
	PRIVATE
		Ast_node.cpp
		Ast.cpp)