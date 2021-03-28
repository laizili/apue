file(GLOB APUE_SRC *.c)
add_library(apue ${APUE_SRC})
target_include_directories(apue PUBLIC ../include)