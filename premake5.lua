project "nvrhi"
	kind "SharedLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "off"

	targetdir (binOutputDir)
    objdir (IntermediatesOutputDir)

	files
	{
		"include/**.h",

		"src/validation/**.h",
		"src/validation/**.cpp",
		"src/common/**.h",
		"src/common/**.cpp",
	
		"src/vulkan/**.h",
		"src/vulkan/**.cpp",

		"rtxmu/include/rtxmu/AccelStructManager.h",
		"rtxmu/include/rtxmu/VulkanSuballocator.h",
		"rtxmu/include/rtxmu/Suballocator.h",
		"rtxmu/include/rtxmu/VkAccelStructManager.h",
		"rtxmu/include/rtxmu/Logger.h",

		"rtxmu/src/VulkanSuballocator.cpp",
		"rtxmu/src/Logger.cpp",
		"rtxmu/src/VkAccelStructManager.cpp",
	}

	includedirs
    {
		"include",
		"rtxmu/include/",
		"%{IncludeDir.Vulkan_Headers}",
    }

	defines
	{
		"NVRHI_WITH_RTXMU",
		"NVRHI_SHARED_LIBRARY_BUILD"
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "system:windows"
		systemversion "latest"
		files
		{
			"src/common/dxgi-format.h",
			"src/common/dxgi-format.cpp",
			"src/d3d11/**.h",
			"src/d3d11/**.cpp",
	
			"src/common/versioning.h",
			"src/d3d12/**.h",
			"src/d3d12/**.cpp",
			
			"rtxmu/include/rtxmu/D3D12AccelStructManager.h",
			"rtxmu/include/rtxmu/D3D12Suballocator.h",
			"rtxmu/src/D3D12Suballocator.cpp",
			"rtxmu/src/D3D12AccelStructManager.cpp",
	
			_ACTION:match("vs") and "tools/nvrhi.natvis" or nil
		}

		links
		{
			"DXGI.lib",
			"D3D11.lib",
			"D3D12.lib",
			"dxguid.lib"
		}

		defines 
		{
			"VK_USE_PLATFORM_WIN32_KHR",
			"NOMINMAX"
		}
	
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