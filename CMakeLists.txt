cmake_minimum_required(VERSION 3.30)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

add_executable(main main.cpp
        src/StateManager.h
        src/colorScheme.h

        def/GameManager.cpp
        src/GameManager.h
        src/GameState.h
        def/TitleState.cpp
        src/TitleState.h
        def/Button.cpp
        src/Button.h
        def/PlayingState.cpp
        src/PlayingState.h
        def/GridCell.cpp
        src/GridCell.h
)

target_link_libraries(main PRIVATE
        SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System
)



