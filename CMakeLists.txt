cmake_minimum_required(VERSION 3.2)

# Definitions
set(PROJECT_NAME_STR file_duplicate)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Project title and define versioning
project(${PROJECT_NAME_STR})

# Include paths
set(${PROJECT_SOURCE_DIR}/src)
set(${PROJECT_SOURCE_DIR}/shared)

# Gather all sources except the main entry point
file(GLOB_RECURSE INC_FILES src/*/*.hpp)
file(GLOB_RECURSE SRC_FILES src/*/*.cpp)

# Dependencies
find_package(Boost COMPONENTS filesystem REQUIRED)


# Assign the include directories
include_directories(${Boost_INCLUDE_DIRS})

# Build
#set(SOURCE_FILES src/main.cpp $<TARGET_OBJECTS:demo_objects>)
set(SOURCE_FILES src/main.cpp ${INC_FILES} ${SRC_FILES})
add_executable(file_duplicate ${SOURCE_FILES})
target_link_libraries(file_duplicate ${Boost_LIBRARIES})