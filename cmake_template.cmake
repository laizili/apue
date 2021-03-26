file(GLOB PROGSRCS *.c)
foreach (PROG_SRC ${PROGSRCS})
    # 获取文件基本名称
    get_filename_component(PROG ${PROG_SRC} NAME_WLE)
    add_executable(${PROG} ${PROG_SRC})
#    target_include_directories(${PROG} PRIVATE ../include)
    target_link_libraries(${PROG} PRIVATE apue)
endforeach ()