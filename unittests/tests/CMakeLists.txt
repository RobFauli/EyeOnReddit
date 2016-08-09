include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})



find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        )

add_executable(runTests Subreddit_tests.cpp)

target_link_libraries(runTests
        Qt5::Core
        backend
        gtest gtest_main)