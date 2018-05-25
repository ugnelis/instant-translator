cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(glog-download NONE)

include(ExternalProject)

ExternalProject_Add(glog
        SOURCE_DIR "@GLOG_DOWNLOAD_ROOT@/glog-src"
        BINARY_DIR "@GLOG_DOWNLOAD_ROOT@/glog-build"
        GIT_REPOSITORY
        https://github.com/google/glog.git
        GIT_TAG
        v0.3.5
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND "")
