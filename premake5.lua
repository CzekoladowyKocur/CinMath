WorkspaceName = "CinMath"
OutputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
CinMath = "CinMath"
UnitTests = "UnitTests"

workspace (WorkspaceName)
	architecture "x64"
	platforms "x64"
	targetdir (OutputDirectory)
	startproject (UnitTests) 

	configurations 
	{ 
		"Debug", 
		"Release",
	}

	flags 
	{
		"MultiProcessorCompile",
	}

	warnings "Extra" -- Warning level

	filter "configurations:Debug"
		defines "CIN_DEBUG" -- Engine define
		symbols "On" -- Specifies whether the compiler should generate debug symbols
		optimize "Off" -- Disables Optimization
		-- optimize "Debug" -- Optimization with some debugger step-through support
		runtime "Debug" -- Specifies the type of runtime library to use
		staticruntime "on" -- Sets runtime library to "MultiThreaded" instead of "MultiThreadedDLL"

	filter "configurations:Release"
		defines "CIN_RELEASE"
		defines "NDEBUG" -- Explicitly define NDEBUG
		symbols "On" 
		optimize "On" 
		runtime "Release"
		staticruntime "on"

		-- Platforms --
	filter "system:windows"
		defines "CIN_PLATFORM_WINDOWS"
		systemversion "latest"

	filter "system:linux"
		defines "CIN_PLATFORM_LINUX"

	filter "system:macosx"
		defines "CIN_PLATFORM_MACOS"

	filter "system:ios"
		defines "CIN_PLATFORM_IOS"

	filter "system:android"
		defines "CIN_PLATFORM_ANDROID"

group "ThirdParty"
include "ThirdParty"
group ""

project (CinMath)
	location (CinMath)
	language "C++"
	cppdialect "C++20"
	kind "Utility"

	targetdir ("bin/" .. (OutputDirectory) .. "/%{prj.name}")
	objdir ("bin-int/" .. (OutputDirectory) .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/include/CinMath/**.h",
		"%{prj.name}/include/CinMath/**.inl",
	}

	includedirs
	{
	}

project (UnitTests)
	location (UnitTests)
	language "C++"
	cppdialect "C++20"
	kind "ConsoleApp"

	targetdir ("bin/" .. (OutputDirectory) .. "/%{prj.name}")
	objdir ("bin-int/" .. (OutputDirectory) .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/src/UnitTests.h",
		"%{prj.name}/src/Benchmark.h",
		
		"%{prj.name}/src/UnitTests.cpp",
		"%{prj.name}/src/Benchmark.cpp",

		"%{prj.name}/src/Main.cpp",
	}

	includedirs
	{
		"CinMath/include",
		"ThirdParty/glm",
	}

project ("Examples")
	location ("Examples")
	language "C++"
	cppdialect "C++20"
	kind "ConsoleApp"

	targetdir ("bin/" .. (OutputDirectory) .. "/%{prj.name}")
	objdir ("bin-int/" .. (OutputDirectory) .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/src/Example.cpp",
	}

	includedirs
	{
		"CinMath/include",
		"ThirdParty/glm",
	}