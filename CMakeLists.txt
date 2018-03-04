cmake_minimum_required(VERSION 3.8)
project(instant_translator)

set(CMAKE_CXX_STANDARD 11)

# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Add Qt CMake path.
set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)
# Add a compiler flag.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find the QtWidgets library.
find_package(Qt5Widgets REQUIRED)

# Generate code from UI files.
qt5_wrap_ui(UI_HEADERS mainwindow.ui)

# Tell CMake to create the executable.
add_executable(instant_translator main.cpp mainwindow.cpp ${UI_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(instant_translator Qt5::Widgets)
