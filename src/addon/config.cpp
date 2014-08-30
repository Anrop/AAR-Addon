class CfgPatches 
{
	class xea_testExtension
	{
		units[] = { };
		weapons[] = { };
		requiredVersion = 0.100000;
		requiredAddons[] = {"CBA_Extended_EventHandlers"};
		version = "1";
		projectName = "ARMA Stat track";
		author = "xealot";
	};
};

class Extended_PostInit_EventHandlers 
{
    class xea_armastat
	{
        Init = "call compile preprocessFileLineNumbers '\xea_armastat\init.sqf'";
	};
};

//class TPW_CIVS_Key_Setting 
//	{
//	#include "\userconfig\TPW_CIVS\TPW_CIVS.hpp"
//	};