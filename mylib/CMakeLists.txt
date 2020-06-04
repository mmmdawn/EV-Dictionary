project(mylib)

add_library(sqlite STATIC sqlite3.c)
# AUX_SOURCE_DIRECTORY(./ SQLITE_SRC)
# add_library(sqlite STATIC ${SQLITE_SRC})
