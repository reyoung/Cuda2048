include_directories(${PROJECT_SOURCE_DIR}/libs/lib2048)
set(APP_SRC main.cpp)
add_executable(console_app ${APP_SRC})
target_link_libraries(console_app lib2048)
