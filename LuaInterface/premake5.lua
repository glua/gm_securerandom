defines "GMMODULE"
includedirs "src"

local target_suffixes = {

	bsd       = "_linux",
	linux     = "_linux",
	solaris   = "_linux",
	windows   = "_win32",
	macosx    = "_osx"  ,

}

local function GetTargetPrefix()
	
	local name = project().name
	
	if 	name:sub(1,3) == "gm_" or
		name:sub(1,5) == "gmsv_" or
		name:sub(1,5) == "gmcl_" then
			
		return ""
		
	end
	
	return "gm_"
	
end

targetprefix		( GetTargetPrefix() )
targetextension		".dll"
targetsuffix		( target_suffixes[ os.get() ] )

