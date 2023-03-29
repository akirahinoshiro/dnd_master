INCLUDE(CTest)
FILE(GLOB TESTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

FOREACH(X IN LISTS TESTS)
    get_filename_component(tests ${X} NAME_WE)
    ADD_EXECUTABLE(${tests}
        ${X}
        ${CPP_FILES}
        ${HEADER_FILES}
    )
    SET_TARGET_PROPERTIES(${tests} PROPERTIES DEBUG_POSTFIX _d)
    target_link_libraries(${tests})

    if(UNIX)
        target_link_libraries(${tests} Threads::Threads)
    endif()

    INSTALL(TARGETS ${tests}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
    add_test(NAME ${tests}_functional COMMAND $<TARGET_FILE:${tests}>)
    add_test(NAME ${tests}_memory_check
        COMMAND valgrind
        --error-exitcode=1
        --tool=memcheck
        --leak-check=full
        --errors-for-leak-kinds=definite
        --show-leak-kinds=definite $<TARGET_FILE:${tests}>
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
    add_test(NAME ${tests}_callgrind
        COMMAND valgrind
        --tool=callgrind
        --dump-instr=yes
        --instr-atstart=yes
        -v -d
        $<TARGET_FILE:${tests}>
    )
ENDFOREACH()