cmake_minimum_required(VERSION 3.20.0)

set(TARGET bytes)
project(${TARGET} VERSION 0.1.0 LANGUAGES C CXX)

# 툴채인을 포함시킵니다.
include("ToolChain/functions.cmake")
include("ToolChain/conandeps_legacy.cmake")

# 빌드 타입이 지정되어 있지 않을 경우 "Debug"를 기본 빌드 타입으로 지정합니다.
if(NOT EXISTS CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Debug")
endif()

message("bin_dir: ${CMAKE_BINARY_DIR}")
message("src_dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# Configure에 따른 출력 디렉토리를 지정합니다.(Debug, Release, MinSizeRel, RelWithDebInfo 등)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} UPPER_OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${UPPER_OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPER_OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${UPPER_OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG}")
endforeach()

message("ok - ${CMAKE_CURRENT_SOURCE_DIR}")

# 소스 파일이 존재하는 경우 활성화 필요하다.
# file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
# add_library(${TARGET} STATIC ${SRC_FILES})
add_library(${TARGET} INTERFACE) # 헤더 파일만 존재하므로 INTERFACE를 사용한다.
add_library(${TARGET}::${TARGET} ALIAS ${TARGET})

make_group_by_path(${CMAKE_CURRENT_SOURCE_DIR} "${SRC_FILES}")
add_header_files(${TARGET})

set_property(TARGET ${TARGET}
    PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

# target_include_directories(${TARGET}
# PUBLIC
# ${CMAKE_CURRENT_SOURCE_DIR}/Include
# )
target_include_directories(${TARGET}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

# target_link_libraries(${TARGET} ${CONANDEPS_LEGACY})
target_link_libraries(${TARGET}
    INTERFACE
    ${CONANDEPS_LEGACY}
)

add_subdirectory(Tests)
add_dependencies(Tests ${TARGET})