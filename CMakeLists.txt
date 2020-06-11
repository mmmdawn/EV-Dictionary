cmake_minimum_required(VERSION 3.0)
project(Dictionary C)
set(CMAKE_C_STANDARD 99)
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(sqlite3)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER} -rdynamic -no-pie -fexceptions -std=c99 -Wno-deprecated-declarations )
message(STATUS "Include: ${GTK3_INCLUDE_DIRS}\n LIB_DIR: ${GTK3_LIBRARY_DIRS} \n CFLAGS_OTHERS: ${GTK3_CFLAGS_OTHER} \n LIBS: ${GTK3_LIBRARIES}")

add_executable(Penguin_Dictionary main.c)
target_link_libraries(Penguin_Dictionary ${GTK3_LIBRARIES} sqlite pthread dl)

