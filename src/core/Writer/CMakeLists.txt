add_library(Codegen SHARED)
target_sources(Codegen
	PRIVATE
		Code_generator.cpp
		Writer.cpp)