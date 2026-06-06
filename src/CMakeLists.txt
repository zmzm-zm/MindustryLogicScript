file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)
add_executable(mls ${SOURCES}
        ../include/backend/logger/Logger.hpp)
target_include_directories(mls
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/third_party/include
)