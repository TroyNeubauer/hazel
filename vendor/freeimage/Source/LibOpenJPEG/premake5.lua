project "freeimage-libopenjpeg"
	kind "StaticLib"
	language "C"
	systemversion "latest"
	
	targetdir ("../../../../../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../../../../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"*.c",
		"*.h",
	}

	defines
	{
		"USE_JPIP",
		"OPJ_STATIC",
	}

	includedirs
	{
		"../../../zlib/include/",--Use /Hazel/vendor/zlib headers
	}
	
