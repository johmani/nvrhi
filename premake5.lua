project "nvrhi"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"
    location (projectLocation)
    targetdir (binOutputDir)
    objdir (IntermediatesOutputDir)

    files {

        "include/**.h",
        "src/validation/**.h",
        "src/common/**.h",

        "src/validation/**.cpp",
        "src/common/**.cpp",

        "*.lua",
    }

    removefiles {

        "src/common/dxgi-format.h",
        "src/common/dxgi-format.cpp",
    }

    if RHI.enableVulkan or RHI.enableD3D12 then
        files {

            "rtxmu/include/rtxmu/AccelStructManager.h",
            "rtxmu/include/rtxmu/Suballocator.h",
            "rtxmu/include/rtxmu/Logger.h",
            "rtxmu/src/Logger.cpp",
        }
    end

    includedirs {

        "include",
        "rtxmu/include/",
    }

    defines {

        "NVRHI_WITH_RTXMU",
        "NVRHI_SHARED_LIBRARY_BUILD"
    }

    filter "system:linux"
        pic "On"
        systemversion "latest"
        if RHI.enableVulkan then
            defines { "NVRHI_HAS_VULKAN" , "VK_USE_PLATFORM_WIN32_KHR" }
            files {
                "src/vulkan/**.h",
                "src/vulkan/**.cpp",

                "rtxmu/include/rtxmu/VkAccelStructManager.h",
                "rtxmu/include/rtxmu/VulkanSuballocator.h",
                "rtxmu/src/VkAccelStructManager.cpp",
                "rtxmu/src/VulkanSuballocator.cpp",
            }
        end

    filter "system:windows"
        systemversion "latest"
        files {

            "src/common/dxgi-format.h",
            "src/common/dxgi-format.cpp",

            _ACTION:match("vs") and "tools/nvrhi.natvis" or nil
        }

        links {

            "DXGI.lib",
            "dxguid.lib"
        }

        defines {

            "NOMINMAX",
        }

        if RHI.enableD3D11 then
            links { "D3D11.lib" }
            defines { "NVRHI_HAS_D3D11" }
            files {

                "src/d3d11/**.h",
                "src/d3d11/**.cpp",
            }
        end

        if RHI.enableD3D12 then
            links { "D3D12.lib" }
            defines { "NVRHI_HAS_D3D12" }
            files {

                "src/d3d12/**.h",
                "src/d3d12/**.cpp",

                "rtxmu/include/rtxmu/D3D12AccelStructManager.h",
                "rtxmu/include/rtxmu/D3D12Suballocator.h",
                "rtxmu/src/D3D12AccelStructManager.cpp",
                "rtxmu/src/D3D12Suballocator.cpp",
            }

            includedirs {
              
                "%{IncludeDir.DirectX_Headers}/directx",
            }
        end

        if RHI.enableVulkan then
            defines { "NVRHI_HAS_VULKAN" , "VK_USE_PLATFORM_WIN32_KHR" }
            files {

                "src/vulkan/**.h",
                "src/vulkan/**.cpp",
                "rtxmu/include/rtxmu/VkAccelStructManager.h",
                "rtxmu/include/rtxmu/VulkanSuballocator.h",
                "rtxmu/src/VkAccelStructManager.cpp",
                "rtxmu/src/VulkanSuballocator.cpp",
            }

            includedirs {
              
                "%{IncludeDir.Vulkan_Headers}",
            }
        end

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        runtime "Release"
        optimize "Speed"
        symbols "Off"
