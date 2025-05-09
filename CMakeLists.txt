cmake_minimum_required(VERSION 3.30)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 20)

find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

add_executable(main main.cpp
        src/BoardState.h
        src/colorScheme.h)

target_link_libraries(main PRIVATE
        imgui::imgui
        SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System
        ImGui-SFML::ImGui-SFML
)



