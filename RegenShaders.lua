include "Premake/common.lua"
include "Premake/extensions.lua"

workspace "Game"

	location ""
	startproject "Game"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Retail"
	}
		
-- include for common stuff 
include "Premake/common.lua"
	
include (dirs.external)
include (dirs.engine)

externalproject ("Game") 
	location (dirs.projectfiles)
	kind "ConsoleApp"



