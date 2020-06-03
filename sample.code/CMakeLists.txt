project(sample.code)

add_executable(insert sqlite/insert.c)
add_executable(select sqlite/select.c)
foreach(example insert select)
  target_link_libraries(${example} sqlite pthread dl)
endforeach(example)
