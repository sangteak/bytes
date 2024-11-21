set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "$ORIGIN")

if(MSVC)
    add_compile_definitions(
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        _CRT_SECURE_NO_WARNINGS
        RAPIDJSON_NOMEMBERITERATORCLASS
		BOOST_ASIO_DISABLE_NOEXCEPT
    )

    add_compile_options(
        /std:c++17
        /utf-8
    )
else()

	add_compile_definitions(
        NOMINMAX
        _CRT_SECURE_NO_WARNINGS
        RAPIDJSON_NOMEMBERITERATORCLASS
		BOOST_ASIO_DISABLE_NOEXCEPT
		BOOST_LOCALE_HIDE_AUTO_PTR
	)

    add_compile_options(
        -std=c++17
        -fPIC
    )
endif()
