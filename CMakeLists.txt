cmake_minimum_required(VERSION 3.0)
project(Dictionary C)
set(CMAKE_C_STANDARD 99)
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(mylib)
add_subdirectory(sample.code)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(gtk testgtk/testgtk.c)
target_link_libraries(gtk ${GTK3_LIBRARIES} sqlite pthread dl )