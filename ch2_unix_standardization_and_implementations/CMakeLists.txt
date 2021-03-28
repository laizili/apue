include(../cmake_template.cmake)

add_custom_command(
        OUTPUT confdetector.c
        COMMAND python3 "${CMAKE_CURRENT_LIST_DIR}/make_detector.py"
        "${CMAKE_CURRENT_LIST_DIR}/sysconf.sym" "${CMAKE_CURRENT_LIST_DIR}/pathconf.sym" "./confdetector.c")
add_executable(confdetector confdetector.c)
target_link_libraries(confdetector PRIVATE apue)

add_custom_command(
        OUTPUT optdetector.c
        COMMAND python3 "${CMAKE_CURRENT_LIST_DIR}/make_detector.py"
        "${CMAKE_CURRENT_LIST_DIR}/sysopt.sym" "${CMAKE_CURRENT_LIST_DIR}/pathopt.sym" "./optdetector.c")
add_executable(optdetector optdetector.c)
target_link_libraries(optdetector PRIVATE apue)