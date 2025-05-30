cmake_minimum_required(VERSION 3.18)
project(vokabeltrainer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion")

find_package(wxWidgets REQUIRED COMPONENTS core base)
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

find_package(SQLiteCpp REQUIRED)

set(CPP_SRCS
    vokabeltrainer.cpp
    input.cpp
    database.cpp
)

add_executable(${PROJECT_NAME} ${CPP_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} SQLiteCpp)

# ============================
# Testing
# ============================

include(CTest)
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(database_tests
    database.cpp
    database_test.cpp
)

target_include_directories(database_tests PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(database_tests PRIVATE ${wxWidgets_LIBRARIES} Catch2::Catch2WithMain SQLiteCpp)

include(Catch)
catch_discover_tests(database_tests)
