add_rules("mode.release","mode.debug")



target("tests")
	set_kind("binary")
	set_warnings("none")
	set_languages("cxx11")
	add_files("tests/**.cpp");
	add_headerfiles("include/**.hpp")

	add_headerfiles("tests/**.hpp")
	remove_files("tests/**/*_test.cpp")
	remove_files("tests/**/detected_*.cpp")
	add_deps("extra_traits")
	set_default(false)


target("extra_traits")
	set_kind("headeronly")
	set_languages("cxx20")
	add_includedirs("include",{public=true})
	add_headerfiles("include/zxshady/**.hpp")
	--set_warnings("allextra", "error")
	set_policy("build.sanitizer.address", false)

  add_cxflags("cl::-Zc:__cplusplus",{public = true})
	set_default(true)
	
