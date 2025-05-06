cmake_minimum_required(VERSION "3.19.2")

# set(CMAKE_MESSAGE_LOG_LEVEL "WARNING")

project("main")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS_TEST_INIT "--rerun-failed --output-on-failure")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.c")
add_executable("${CMAKE_PROJECT_NAME}" "${MY_SOURCES}" src/main.c)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE m)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -O3)


# # enable testing functionality
# enable_testing()

# # define tests

# file(GLOB_RECURSE TEST_SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.c")


# foreach(test_src ${TEST_SRCS})

#     get_filename_component(test_name ${test_src} NAME_WE)
#     #! piccolo problema, questo ricompila tutto, dovrebbe solo linkare i file già compilati
#     #! da capire in seguito
#     add_executable(${test_name} ${test_src} ${MY_SOURCES})

#     target_link_libraries(${test_name} PRIVATE m)


#     set_target_properties( 
#         ${test_name} 
#         PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
#     )

#     add_test(
#         NAME ${test_name}
#         COMMAND ${test_name} --rerun-failed --output-on-failure
#     )
    
# endforeach(test_src)