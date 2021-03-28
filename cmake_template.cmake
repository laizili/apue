file(GLOB PROGSRCS *.c)
foreach (PROG_SRC ${PROGSRCS})
    # 获取源文件名
    get_filename_component(PROG ${PROG_SRC} NAME_WLE)
    message("${PROG} ${PROG_SRC}")
    add_executable(${PROG} ${PROG_SRC})
    target_link_libraries(${PROG} PRIVATE apue)
endforeach ()