class CfgPatches
{
	class anrop_aar
	{
		units[] = { };
		weapons[] = { };
		requiredVersion = 0.100000;
		requiredAddons[] = {"CBA_Extended_EventHandlers"};
		version = "1";
		projectName = "Anrop AAR";
		author = "Anrop";
	};
};

class CfgFunctions
{
	class anrop_aar
	{
		class events
		{
			file = "anrop_aar\events";
			class eventHit {};
			class eventKilled {};
			class eventMissionEnded {};
			class eventPlayerConnected {};
			class eventPlayerDisconnected {};
			class eventUnitDeleted {};
			class eventUnitFired {};
			class eventVehicleDeleted {};
			class eventVehicleFired {};
		};
		class functions
		{
			file = "anrop_aar\functions";
			class addUnitEventHandlers {};
			class addVehicleEventHandlers {};
			class getUnitName {};
			class init {};
			class reportMarkerPositions {};
			class reportUnitPositions {};
			class reportVehiclePositions {};
			class sendEvent {};
			class sendJson {};
			class serializeJson {};
			class serializeMarker {};
			class serializeMission {};
			class serializePlayer {};
			class serializePosition {};
			class serializeProjectile {};
			class serializeUnit {};
			class serializeVehicle {};
			class trackProjectile {};
		};
	};
};

class Extended_PostInit_EventHandlers
{
    class anrop_aar
	{
        Init = "call anrop_aar_fnc_init";
	};
};
