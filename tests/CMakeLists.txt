macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} PRIVATE library GTest::gtest_main)

    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTOR ${PROJECT_SOURCE_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )

    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(grading_tests grading_tests.cpp)
