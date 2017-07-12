solution "gm_securerandom"

	language "C++"
	location "project"
	flags { "StaticRuntime", "C++11" }
	targetdir "bin"
	includedirs { "LuaInterface/src/" }
	architecture "x86"

	configurations { "Release" }

	configuration "Release"
		optimize "On"

	project "gm_securerandom"
		defines { "GMMODULE" }
		files {
			"LuaInterface/src/GarrysMod/Lua/*.h",
			"src/*.h",
			"src/*.hpp",
			"src/*.hxx",
			"src/*.cpp",
			"src/*.cxx"
		}
		kind "SharedLib"
