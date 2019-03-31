file(GLOB test_SRC
    "**/*.cpp"
)

set(TEST_EXE_NAME anrop_aar_test)
add_executable(${TEST_EXE_NAME} main.cpp ${test_SRC})
target_link_libraries(${TEST_EXE_NAME} anrop_aar CONAN_PKG::catch2)

include(CTest)
include(Catch)
catch_discover_tests(${TEST_EXE_NAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
