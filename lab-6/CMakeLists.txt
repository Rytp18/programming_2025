cmake_minimum_required(VERSION 3.16)

project(lab-6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_library(lab6_common
    shell.h
    shell.cpp
)
target_link_libraries(lab6_common PUBLIC Qt6::Core)

add_executable(lab-6-program1
    program1_main.cpp
    program1window.h
    program1window.cpp
    program1.ui
)
target_link_libraries(lab-6-program1 PRIVATE
    lab6_common
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

add_executable(lab-6-program2
    program2_main.cpp
    program2window.h
    program2window.cpp
    program2.ui
)
target_link_libraries(lab-6-program2 PRIVATE
    lab6_common
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)