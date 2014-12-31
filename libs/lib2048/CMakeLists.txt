FILE(GLOB LIB_SRC *.cpp *.c)
find_package(Boost)

add_library(lib2048 ${LIB_SRC})
set_target_properties(lib2048 PROPERTIES OUTPUT_NAME "2048")