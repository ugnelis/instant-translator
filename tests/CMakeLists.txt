
# Find the Qt libraries.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Concurrent REQUIRED)

# Qt5 libraries.
set(QT5_LIBRARIES
        Qt5::Widgets
        Qt5::Network
        Qt5::Concurrent)

# UI files.
qt5_wrap_ui(UI_HEADERS ${PROJECT_SOURCE_DIR}/src/mainwindow.ui)

set(RESOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/resources.qrc)

qt5_add_resources(RESOURCE_FILES_ADDED ${RESOURCE_FILES})

# Include source directory.
include_directories("${PROJECT_SOURCE_DIR}/src")

# Source files.
set(SOURCE_FILES
        utils/language_test.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/language.cpp
        ${PROJECT_SOURCE_DIR}/src/utils/language.h)

# Tell CMake to create the executable.
add_executable(unit_tests ${SOURCE_FILES} ${RESOURCE_FILES_ADDED} ${UI_HEADERS})

# Use the Widgets module from Qt5.
target_link_libraries(unit_tests ${QT5_LIBRARIES} gtest_main)

# Add tests.
add_test(
        NAME unit_tests
        COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
