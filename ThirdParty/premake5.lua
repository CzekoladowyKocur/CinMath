project "glm"
	location("%{wks.location}" .. "/ThirdParty/glm/")
	kind "Utility"

	targetdir ("%{wks.location}/bin/" .. (OutputDirectory) .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. (OutputDirectory) .. "/%{prj.name}")

	files
	{
		"glm",
	}