cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(AOC_DAY "Day16")
project(${AOC_DAY} LANGUAGES CXX)

set(ITEM_HEADERS ${AOC_DAY}_headers)
set(ITEM_SUBMISSION ${AOC_DAY}_submission)
set(ITEM_COMMON ${AOC_DAY}_common)
set(ITEM_EXEC ${AOC_DAY}_exe)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest"
    GIT_TAG        release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include ${googletest_SOURCE_DIR}/googletest/include)

add_library(${ITEM_SUBMISSION} SHARED src/solution.cpp)

include(CTest)

add_executable(
  ${ITEM_EXEC}
  tests/test_solution.cpp
)

target_link_libraries(
  ${ITEM_EXEC}
  GTest::gtest_main
  ${ITEM_SUBMISSION}
)

include(GoogleTest)
gtest_discover_tests(${ITEM_EXEC})
