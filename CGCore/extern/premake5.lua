project "imgui"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/*.cpp",
		"%{prj.name}/*.h",
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
project "glfw"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/GLFW/glfw3.h",
		"%{prj.name}/include/GLFW/glfw3native.h",
		"%{prj.name}/src/glfw_config.h",
		"%{prj.name}/src/context.c",
		"%{prj.name}/src/init.c",
		"%{prj.name}/src/input.c",
		"%{prj.name}/src/monitor.c",
		"%{prj.name}/src/vulkan.c",
		"%{prj.name}/src/window.c"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"%{prj.name}/src/win32_init.c",
			"%{prj.name}/src/win32_joystick.c",
			"%{prj.name}/src/win32_monitor.c",
			"%{prj.name}/src/win32_time.c",
			"%{prj.name}/src/win32_thread.c",
			"%{prj.name}/src/win32_window.c",
			"%{prj.name}/src/wgl_context.c",
			"%{prj.name}/src/egl_context.c",
			"%{prj.name}/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.c"
    }
    includedirs
    {
        "%{prj.name}/include/"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

