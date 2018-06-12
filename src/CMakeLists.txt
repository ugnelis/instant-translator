cmake_minimum_required(VERSION 3.5)
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

# Find the Qt libraries.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Concurrent REQUIRED)

# Qt5 libraries.
set(QT5_LIBRARIES
        Qt5::Widgets
        Qt5::Network
        Qt5::Concurrent)

set(OTHER_LIBRARIES
        glog)

# UI files.
qt5_wrap_ui(UI_HEADERS mainwindow.ui dialogs/settingsdialog.ui)

set(RESOURCE_FILES
        resources.qrc)

qt5_add_resources(RESOURCE_FILES_ADDED ${RESOURCE_FILES})

# Source files.
set(SOURCE_FILES
        apis/api.h
        apis/googleapi.cpp
        apis/googleapi.h
        dialogs/settingsdialog.cpp
        dialogs/settingsdialog.h
        dialogs/settingsdialog.ui
        utils/language.cpp
        utils/language.h
        utils/requestmanager.cpp
        utils/requestmanager.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui)

# Tell CMake to create the executable.
add_executable(instant_translator ${SOURCE_FILES} ${RESOURCE_FILES_ADDED} ${UI_HEADERS})

# Use the Widgets module from Qt5.
target_link_libraries(instant_translator ${QT5_LIBRARIES} ${OTHER_LIBRARIES})
