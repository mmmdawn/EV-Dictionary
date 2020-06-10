 project(sample.code)

 add_executable(insert sqlite/insert.c)
 add_executable(selectall sqlite/selectall.c)
 add_executable(search sqlite/search.c)
 add_executable(hoangmangstyle sqlite/hoangmangstyle.c)
 add_executable(add sqlite/add.c)
 add_executable(delete sqlite/delete.c)
 add_executable(update sqlite/update.c)

 foreach(example insert selectall search hoangmangstyle add delete update)
   target_link_libraries(${example} sqlite pthread dl)
 endforeach(example)
