cmake_minimum_required(VERSION 3.21)

set (CMAKE_BUILD_TYPE "Debug")
set (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set (CMAKE_CXX_FLAGS "-Wall -std=c++17")
set (CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
set (CMAKE_CXX_FLAGS_MINSIZEREL_INIT "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE_INIT "-O4 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

FILE (
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/media"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

project(CMakeSFMLProject)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject ../src/main.cpp ../src/pattern.cpp ../src/puzzle.cpp ../src/picture.cpp ../src/binary_tree.cpp)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)
if(WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject>, COMMAND_EXPAND_LISTS)
endif()

install(TARGETS CMakeSFMLProject)