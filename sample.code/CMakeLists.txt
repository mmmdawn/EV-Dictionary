project(sample.code)

add_executable(insert sqlite/insert.c)

foreach(example insert)
  target_link_libraries(${example} sqlite pthread dl)
endforeach(example)
