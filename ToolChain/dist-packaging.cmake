set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(INSTALL_DIR install)
if (WIN32)
set(BUILD_TARGET_DIRECTORY build_windows)
else()
set(BUILD_TARGET_DIRECTORY build_linux)
endif()

# Ignore component list
list(APPEND EXCLUDE_COMPONENTS "PerformanceClient")
list(APPEND EXCLUDE_COMPONENTS "PerformanceServer")
list(APPEND EXCLUDE_COMPONENTS "Example")

# copy common library
install(
    DIRECTORY       ${CMAKE_SOURCE_DIR}/Common/Include
    DESTINATION     ${INSTALL_DIR}/ThirdParty/SGSP
)

install(
    TARGETS         Common
    DESTINATION     ${INSTALL_DIR}/ThirdParty/SGSP/Lib/${CMAKE_BUILD_TYPE}
)

if(MSVC)
    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/Common.pdb"
        CONFIGURATIONS Debug
        DESTINATION ${INSTALL_DIR}/ThirdParty/SGSP/Lib/${CMAKE_BUILD_TYPE}
    )
endif()

# copy components..��,��,
file(GLOB COMPONENTS_DIRS LIST_DIRECTORIES=true ${CMAKE_SOURCE_DIR}/Components/*)
foreach(ch ${COMPONENTS_DIRS})
    if(IS_DIRECTORY ${ch})
        if(EXISTS ${ch}/CMakeLists.txt)
            string(FIND ${ch} "/" CH_OFFSET REVERSE)
            math(EXPR BEGIN "${CH_OFFSET} + 1" OUTPUT_FORMAT DECIMAL)
            string(SUBSTRING ${ch} ${BEGIN} -1 COMPONENT)

            set(IGNORE_INDEX -1)
            list(FIND EXCLUDE_COMPONENTS ${COMPONENT} IGNORE_INDEX)
            if(IGNORE_INDEX EQUAL -1)
                message(STATUS "COMPONENT => ${ch} - ${COMPONENT}")
                list(APPEND TARGET_COMPONENTS ${COMPONENT})
            endif()
        endif()
    endif()
endforeach()

install(
    TARGETS ${TARGET_COMPONENTS}
    RUNTIME DESTINATION ${INSTALL_DIR}/Bin/${CMAKE_BUILD_TYPE} COMPONENT runtime
)

if(MSVC)
    foreach(component ${TARGET_COMPONENTS})
        list(APPEND PDB_FILES "${CMAKE_CURRENT_BINARY_DIR}/Bin/${CMAKE_BUILD_TYPE}/${component}.pdb")    
    endforeach()

    install(
        FILES ${PDB_FILES}
        CONFIGURATIONS Debug
        DESTINATION ${INSTALL_DIR}/Bin/${CMAKE_BUILD_TYPE} COMPONENT Debug
    )
endif()

# find third-party shared libraries
file(
    GLOB 
    SHARED_LIBRARY_LIST 
    LIST_DIRECTORIES=false 
    "${CMAKE_CURRENT_BINARY_DIR}/Bin/${CMAKE_BUILD_TYPE}/*.dll"
    "${CMAKE_CURRENT_BINARY_DIR}/Bin/${CMAKE_BUILD_TYPE}/*.so"
    "${CMAKE_CURRENT_BINARY_DIR}/Bin/${CMAKE_BUILD_TYPE}/*.so.*"
)

foreach(ch ${SHARED_LIBRARY_LIST})
    # get the filename
    string(FIND ${ch} "/" START_OFFSET REVERSE)
    math(EXPR BEGIN "${START_OFFSET} + 1" OUTPUT_FORMAT DECIMAL)
    string(SUBSTRING ${ch} ${BEGIN} -1 FILE_NAME)

    string(FIND ${FILE_NAME} "." END_OFFSET)
    math(EXPR END "${END_OFFSET}" OUTPUT_FORMAT DECIMAL)
    string(SUBSTRING ${FILE_NAME} 0 ${END} SHARED_LIBRARY)

    # exclude component shared libraries
    list(FIND TARGET_COMPONENTS ${SHARED_LIBRARY} INDEX)
    if(INDEX EQUAL -1)
        set(IGNORE_INDEX -1)
        list(FIND EXCLUDE_COMPONENTS ${SHARED_LIBRARY} IGNORE_INDEX)
        if(IGNORE_INDEX EQUAL -1)
            list(APPEND DEPENDENCIES_FILES ${ch})
            message(STATUS "THIRD-PARTY => ${ch}")
        endif()
    endif()
endforeach()

install(
    FILES           ${DEPENDENCIES_FILES} 
	DESTINATION     ${INSTALL_DIR}/Bin/${CMAKE_BUILD_TYPE}
)

# copy tool
install(
    DIRECTORY       ${CMAKE_SOURCE_DIR}/Tool/CLI/bin/Resource
    DESTINATION     ${INSTALL_DIR}/Tool/CLI
)

if (WIN32)
    install(
        FILES           ${CMAKE_SOURCE_DIR}/Tool/CLI/bin/sgsp.exe
        DESTINATION     ${INSTALL_DIR}/Tool/CLI
    )
else()
    install(
        FILES           ${CMAKE_SOURCE_DIR}/Tool/CLI/bin/sgsp
        DESTINATION     ${INSTALL_DIR}/Tool/CLI
    )
endif()

install(
    DIRECTORY       ${CMAKE_SOURCE_DIR}/ToolChain/CMake
	DESTINATION     ${INSTALL_DIR}/ToolChain
	COMPONENT		copy-files
	PATTERN			"dist-packaging.cmake"	EXCLUDE
    PATTERN         "*.bak" EXCLUDE
)

# create Components directory
# SET(ROOT_DIRECTORY_FILES
#    ${CMAKE_SOURCE_DIR}/CMakePresets.json
#    ${CMAKE_SOURCE_DIR}/CMakeLists.txt
# )
# install(
#    FILES           ${ROOT_DIRECTORY_FILES}
#    DESTINATION     install
# )

