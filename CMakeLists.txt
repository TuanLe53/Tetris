cmake_minimum_required(VERSION 3.10.0)
project(Tetris VERSION 0.1.0 LANGUAGES C CXX)

set(SFML_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/SFML-3.1.0")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
list(APPEND CMAKE_PREFIX_PATH "${SFML_ROOT}")

find_package(SFML 3.1.0 COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(Tetris src/main.cpp src/entities/block.cpp src/entities/factory.cpp src/board.cpp )

target_include_directories(Tetris PUBLIC "${SFML_ROOT}/include" "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_directories(Tetris PUBLIC "${SFML_ROOT}/lib")

target_link_libraries(Tetris sfml-graphics sfml-window sfml-system sfml-audio)

add_custom_command(TARGET Tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:Tetris>/assets"
)

if(WIN32)
    add_custom_command(TARGET Tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_ROOT}/bin"
        $<TARGET_FILE_DIR:Tetris>
    )
endif()