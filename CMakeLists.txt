cmake_minimum_required(VERSION 3.1.0)

project(mv_tree)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Resources
list (APPEND RESOURCES ./src/simpletreemodel.qrc)
qt5_add_resources (RCC_SOURCES ${RESOURCES})

set(UI src/mainwindow.ui)
qt5_wrap_ui(UI_HEADERS ${UI})

# Populate a CMake variable with the sources
set(mv_tree
	./src/treeitem.cpp
    ./src/treemodel.cpp
    ./src/mainwindow.cpp
    ./src/main.cpp
)

# Tell CMake to create the helloworld executable
add_executable(helloworld ${RCC_SOURCES} ${UI_HEADERS} ${mv_tree})
# Use the Widgets module from Qt 5
target_link_libraries(helloworld Qt5::Widgets)