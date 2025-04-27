cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_MESSAGE_LOG_LEVEL "WARNING")

project("main")

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable("${CMAKE_PROJECT_NAME}" "${MY_SOURCES}")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE m)



# target_include_directories(main PUBLIC "src/*")
