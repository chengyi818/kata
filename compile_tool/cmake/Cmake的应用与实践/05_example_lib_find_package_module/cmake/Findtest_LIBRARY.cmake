message("find path PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
find_path(test_INCLUDE_DIR
    NAMES test.h
    PATHS ${PROJECT_SOURCE_DIR}/lib/output/include)

find_library(test_LIBRARY
    NAMES test_lib
    PATHS ${PROJECT_SOURCE_DIR}/lib/output/lib)

message("test_INCLUDE_DIR: " ${test_INCLUDE_DIR})
message("test_LIBRARY: " ${test_LIBRARY})

IF (test_INCLUDE_DIR AND test_LIBRARY)
    SET(test_FOUND TRUE)
ENDIF (test_INCLUDE_DIR AND test_LIBRARY)
