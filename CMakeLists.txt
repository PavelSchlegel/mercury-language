cmake_minimum_required(VERSION 3.16)
project(mercury LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

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
