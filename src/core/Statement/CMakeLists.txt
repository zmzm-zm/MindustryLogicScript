add_library(Statement SHARED)
target_sources(Statement
	PRIVATE
		Statement.cpp
		Assignment_statement.cpp
		Operation_statement.cpp)