-- premake5.lua
workspace "VolumetricCloud"
   configurations { "Debug", "Release" }
   systemversion "latest"

project "VolumetricCloud"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
    objdir "bin/int/%{prj.name}/%{cfg.buildcfg}"

    includedirs { 
        "%{prj.location}/src",
        "include/glm",
        "include/stb"
    }
    files {
        "%{prj.location}/src/**.h", 
        "%{prj.location}/src/**.cpp"
    }

    filter "configurations:Debug"
        --   defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        --   defines { "NDEBUG" }
        optimize "On"

project "MapGenerator"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
    objdir "bin/int/%{prj.name}/%{cfg.buildcfg}"

    includedirs { 
        "%{prj.location}/src",
        "include/glm",
        "include/stb"
    }
    files { 
        "%{prj.location}/**.h", 
        "%{prj.location}/**.hpp", 
        "%{prj.location}/**.cpp" 
    }

    filter "configurations:Debug"
    --   defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
    --   defines { "NDEBUG" }
        optimize "On"