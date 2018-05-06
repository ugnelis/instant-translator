cmake_minimum_required(VERSION 3.5)

project(instant_translator)

set (CMAKE_CXX_STANDARD 11)

# Place binaries and libraries according to GNU standards.
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Threading support doesn't exist for some cross compile targets.
find_package(Thread QUIET)

if (CMAKE_THREAD_LIBS_INIT)
    set(gtest_disable_pthreads OFF)
else ()
    message(STATUS "Disabling pthread in Google Test.")
    set(gtest_disable_pthreads ON)
endif ()

# Coverage.
option(COVERAGE "Generate coverage data" OFF)
if (COVERAGE)
    if (CMAKE_COMPILER_IS_GNUCXX)
        include(cmake/coverage.cmake)
        setup_target_for_coverage(project_coverage unit_tests coverage)

        set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
        set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    endif ()
endif ()

# Add source folder.
add_subdirectory(src)

# Add test folder.
include(cmake/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/googletest
)

enable_testing()
add_subdirectory(tests)
