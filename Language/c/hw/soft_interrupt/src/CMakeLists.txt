set(LIB_SOURCES
  softinterrupt.c
)

set(MAIN_SOURCES
  main.c
)

set(HEADERS
  ${CONFIG_HEADER}
  softinterrupt.h
)

add_library(softinterrupt STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main softinterrupt)

install(TARGETS softinterrupt
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/softinterrupt.h
  DESTINATION include)
