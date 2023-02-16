cmake_minimum_required(VERSION 3.16)
project(mercury LANGUAGES CXX C VERSION 0.0.1)

include(FetchContent)
enable_testing()

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME}-lib parser.cpp)
target_include_directories(${PROJECT_NAME}-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
set_target_properties(${PROJECT_NAME}-lib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

add_executable(${PROJECT_NAME}-test test/parser.cpp)
target_link_libraries(${PROJECT_NAME}-test PUBLIC ${PROJECT_NAME}-lib gtest gtest_main)
add_test(NAME ParserTest COMMAND ${PROJECT_NAME}-test)
install(TARGETS ${PROJECT_NAME}-test RUNTIME DESTINATION bin)

add_executable(${PROJECT_NAME}
    main.cpp
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

include(CPack)
