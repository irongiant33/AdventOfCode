cmake_minimum_required(VERSION 3.16)

set(AOC_DAY "Day8")
project(${AOC_DAY} LANGUAGES C)

set(ITEM_HEADERS ${AOC_DAY}_headers)
set(ITEM_SUBMISSION ${AOC_DAY}_submission)
set(ITEM_COMMON ${AOC_DAY}_common)
set(ITEM_TESTS ${AOC_DAY}_test)
set(ITEM_EXEC ${AOC_DAY}_exe)

add_library(${ITEM_SUBMISSION} SHARED "src/day8.c" "include/day8.h")

add_library(${ITEM_TESTS} SHARED "tests/day8_test.c")

add_library(${ITEM_COMMON} SHARED "../common/fileio.c" "../common/doubly_ll.c" "../common/hash_table.c" "../common/common.h")

# add the executable
add_executable(${ITEM_EXEC} tests/main_tests.c "include/day8.h" "src/day8.c")

target_link_libraries(${ITEM_EXEC} ${ITEM_SUBMISSION} ${ITEM_TESTS} ${ITEM_COMMON} cunit)
target_compile_options(${ITEM_EXEC} PUBLIC "-Wall" "-Wextra" "-g")
add_test(${AOC_DAY}_tests ${ITEM_EXEC})
