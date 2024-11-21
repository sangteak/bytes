function(make_group_by_path remove_prefix file_list)
	foreach(f IN ITEMS ${file_list})
		get_filename_component(file_path "${f}" PATH)
		string(REPLACE "${remove_prefix}" "" group_name "${file_path}")
		string(REPLACE "/" "\\" group_name "${group_name}")
		source_group("${group_name}" FILES "${f}")
	endforeach()
endfunction(make_group_by_path)

function(add_header_files target)
    file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/**/*.h)

    target_sources(${target} 
    PRIVATE
        ${HEADER_FILES}
    )
	
	make_group_by_path(${CMAKE_CURRENT_SOURCE_DIR} "${HEADER_FILES}")
endfunction(add_header_files)

function(conan_install conan_build_type)
	set(CMAKE_BUILD_TYPE ${conan_build_type})
	conan_cmake_autodetect(settings)
	conan_cmake_install(PATH_OR_REFERENCE  ../conanfile.py
						BUILD missing
						REMOTE conancenter
						GENERATOR cmake_multi
						SETTINGS ${settings})
endfunction(conan_install)

function(active_unity_build t sl)
	#필수 인자를 사용할 변수로 복사한다.
	#필수인자는
	#	1. target 이름
	#	2. source 목록
	set(_TARGET ${t})
	set(_SOURCE_LIST ${sl})
	
	#추가 인자를 파싱함
	#추가 인자는
	#	1. group 당 file 갯수
	#	2. group 에서 제외할 목록
	list(LENGTH ARGN opt_args_len)
	if(opt_args_len EQUAL 0)
		set(_COUNT_PER_FILE "5")
		set(_EXCLUDE_LIST "")
	elseif(opt_arg_len EQUAL 1)
		list(GET ARGN 0 _COUNT_PER_FILE)
		set(_EXCLUDE_LIST "")
	else()
		list(GET ARGN 0 _COUNT_PER_FILE)
		list(REMOVE_AT ARGN 0)
		set(_EXCLUDE_LIST ${ARGN})
	endif()

	message("-- **** UNITY BUILD START ****")
	message("-- ** TARGET : " ${_TARGET})
	message("-- ** GROUP BY FILE NUM : " ${_COUNT_PER_FILE})
	list(LENGTH _EXCLUDE_LIST el_len)
	if(el_len GREATER 0)
		#제외할 목록 제거함.
		message("-- ** UNITY BUILD EXCLUDE FILES ****")
		foreach (exclude_file IN ITEMS ${_EXCLUDE_LIST})
			message("-- ** - " ${exclude_file})
			list(FILTER _SOURCE_LIST EXCLUDE REGEX ${exclude_file})
		endforeach()
	endif()
	message("-- ***************************")

    list(LENGTH _SOURCE_LIST sl_len)
    if(sl_len EQUAL 0)
        return()
    endif()

	set_target_properties(${_TARGET}
		PROPERTIES
			UNITY_BUILD ON
			UNITY_BUILD_MODE GROUP
	)
	
	MATH(EXPR unity_count "0")
	SET(group_list "")
	
	foreach (src IN ITEMS ${_SOURCE_LIST})
		list(APPEND group_list ${src})
		
		list(LENGTH group_list gr_len)
		if (${gr_len} EQUAL _COUNT_PER_FILE)
			message("-- **** UNITY BUILD GROUP : " ${unity_count} " ****")
			foreach (member IN ITEMS ${group_list})
				message("--   " ${member})
			endforeach()
			set_source_files_properties(${group_list}
				PROPERTIES
					UNITY_GROUP ${unity_count}
			)
			MATH(EXPR unity_count "${unity_count}+1")
			SET(group_list "")
			message("-- *******************************")
		endif()	
	endforeach()
	
	LIST(LENGTH group_list gr_len)
	if (${gr_len} GREATER 0)
		message("-- **** UNITY BUILD GROUP : " ${unity_count} " ****")
		foreach (member IN ITEMS ${group_list})
			message("--   " ${member})
		endforeach()
		set_source_files_properties(${group_list}
			PROPERTIES
				UNITY_GROUP ${unity_count}
		)
		message("-- *******************************")
	endif()
endfunction(active_unity_build)