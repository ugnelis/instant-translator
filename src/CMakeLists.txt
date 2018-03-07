cmake_minimum_required(VERSION 3.8)
project(instant_translator)

set(CMAKE_CXX_STANDARD 11)

# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)
# Add a compiler flag.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add Qt CMake path.
#set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)

# Find the QtWidgets library.
find_package(Qt5Widgets REQUIRED)

# Qt5 libraries.
set(QT5_LIBRARIES Qt5::Widgets)

# UI files.
qt5_wrap_ui(UI_HEADERS mainwindow.ui)

set(RESOURCE_FILES
        resources.qrc)

qt5_add_resources(RESOURCE_FILES_ADDED ${RESOURCE_FILES})

# Source files.
set(SOURCE_FILES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui)

# Tell CMake to create the executable.
add_executable(instant_translator ${SOURCE_FILES} ${RESOURCE_FILES_ADDED} ${UI_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(instant_translator ${QT5_LIBRARIES})
