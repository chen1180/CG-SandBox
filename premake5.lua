workspace "CG-Sandbox"
	architecture "x86_64"
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	startproject "CGSandbox"

outputdir="%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"
--include directories relative to root folder 


IncludeDir={}
IncludeDir["imgui"]="CGCore/extern/imgui"

group "Depencencies"
	include "CGCore/extern/imgui"
group ""

project "CGCore"
	location "CGCore"
	kind "StaticLib"
	language "C++"
	cppdialect "c++17"
	systemversion "latest"
	staticruntime "on"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"%{prj.name}/extern/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.imGui}"

	}
	links{
	}
	pchheader "pch.h"
	pchsource "CGCore/src/pch.cpp"

	filter "system:windows"
		defines{
		"_CRT_SECURE_NO_WARNINGS"
		}
	filter "configurations:Debug"
		defines {"CG_DEBUG"}
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "CG_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "CG_DIST"
		runtime "Release"
		optimize "On"

project "CGSandbox"
	location "CGSandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	systemversion "latest"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"CGCore/src",
		"CGCore/extern/spdlog/include",
		"%{IncludeDir.imGui}"

	}
	links{
		"CGCore"
	}
		filter "system:windows"
		defines{
		"_CRT_SECURE_NO_WARNINGS"
		}
	filter "configurations:Debug"
		defines {"CG_DEBUG"}
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "CG_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "CG_DIST"
		runtime "Release"
		optimize "On"
