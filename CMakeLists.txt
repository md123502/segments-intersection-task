cmake_minimum_required(VERSION 3.18)

project("segments-intersection-task")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        b514bdc898e2951020cbdca1304b75f5950d1f59 # release-1.15.2
)
FetchContent_MakeAvailable(googletest)

add_compile_options("-Wall")
add_compile_options("-pedantic")
add_compile_options("-g")

add_subdirectory(src)

add_subdirectory(tests)
