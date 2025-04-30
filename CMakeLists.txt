cmake_minimum_required(VERSION 3.18)
project(vokabeltrainer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion")


find_package(wxWidgets REQUIRED COMPONENTS core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
find_package(SQLiteCpp REQUIRED)

include(CTest)



set(CPP_SRCS  # all non-main source files
    vokabeltrainer.cpp
    dynamic_events.cpp
)


add_executable(${PROJECT_NAME} ${CPP_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} SQLiteCpp)
