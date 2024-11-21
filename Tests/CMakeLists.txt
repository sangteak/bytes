set(TARGET Tests)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${TARGET} ${SRC_FILES})

make_group_by_path(${CMAKE_CURRENT_SOURCE_DIR} "${SRC_FILES}")
add_header_files(${TARGET})

set_property(TARGET ${TARGET}
    PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)

target_include_directories(${TARGET}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET} ${CONANDEPS_LEGACY})

enable_testing()
add_test(NAME ${TARGET} COMMAND ${TARGET})