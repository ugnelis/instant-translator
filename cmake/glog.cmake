macro(fetch_glog _download_module_path _download_root)
    set(GLOG_DOWNLOAD_ROOT ${_download_root})
    configure_file(
            ${_download_module_path}/glog-download.cmake
            ${_download_root}/CMakeLists.txt
            @ONLY)

    unset(GLOG_DOWNLOAD_ROOT)

    execute_process(
            COMMAND
            "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
            WORKING_DIRECTORY
            ${_download_root})

    execute_process(
            COMMAND
            "${CMAKE_COMMAND}" --build .
            WORKING_DIRECTORY
            ${_download_root})

    add_subdirectory(
            ${_download_root}/glog-src
            ${_download_root}/glog-build)
endmacro()
