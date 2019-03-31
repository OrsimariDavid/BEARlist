cmake_minimum_required ( VERSION 3.13 )

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp testfixture.cpp test.cpp Fake_View.h )
add_executable(runAllTests ${TEST_SOURCE_FILES})

find_package(wxWidgets REQUIRED net gl core base xrc adv)
include(${wxWidgets_USE_FILE})


# for each of your dependent executable/library targets:
target_link_libraries(runAllTests gtest gtest_main core ${wxWidgets_LIBRARIES})