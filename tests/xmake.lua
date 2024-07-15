
target("tests")
	set_kind("binary")
	set_warnings("none")
	set_languages("cxx20")
	add_files("**.cpp");
	add_headerfiles("**.hpp")
	remove_files("*_test.cpp")
	add_deps("extra_traits")
	set_default(false)

