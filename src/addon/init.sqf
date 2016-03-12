// Setup config
xea_stats_hostname = "arma-stats-api.herokuapp.com";
xea_stats_position_reporting = 10;
if (isFilePatchingEnabled) then {
	xea_stats_settings_file = compile preprocessFileLineNumbers "\userconfig\stats\config.sqf";
	if (!isNil "xea_stats_settings_file") then {
		[] call xea_stats_settings_file;
	};
};
xea_extension = "armastat";	// dll

if (isMultiplayer) then {
	/*
		--------------------------------------------------------------------------------------------------------------
					FUNCTIONS INIT
	*/

	call compile preprocessFileLineNumbers "\xea_armastat\functions.sqf";

	/*
		--------------------------------------------------------------------------------------------------------------
					PLUGIN INIT
	*/

	/* Initialize plugin. Get unique ID from server */
	xea_extension callExtension format["setup;%1", xea_stats_hostname];
	_mission = call xea_fnc_serializeMission;
	_missionData = _mission call xea_fnc_serializeJson;
	xea_stattrack_id = xea_extension callExtension format["mission;%1", _missionData];

	/*
		--------------------------------------------------------------------------------------------------------------
					MISSION INIT
	*/

	/* TODO: check if dedicated creates a dummy user for connection events */
	if (isServer) then {
		["xea_armastat_connected", "onPlayerConnected", {
			[_uid, _name] call xea_fnc_playerConnected;
		}] call BIS_fnc_addStackedEventHandler;

		["xea_armastat_disconnected", "onPlayerDisconnected", {
			[_uid, _name] call xea_fnc_playerDisconnected;
		}] call BIS_fnc_addStackedEventHandler;

		addMissionEventHandler ["Ended", { (_this) call xea_fnc_missionEnded }];
	};

	/*
		--------------------------------------------------------------------------------------------------------------
					UNIT INIT
	*/

	/* Attach various eventhandlers on players */
	{
		//_x call xea_fnc_addEventHandlers;
	} forEach allUnits;

	/* Add event handlers to units created during the mission */
	[] spawn {
		while { true } do {
			{
				if (!(_x getVariable ["xea_stattrack", false])) then {
					//_x call xea_fnc_addEventHandlers;
				};
			} foreach allUnits;
			sleep 5;
		};
	};

	/* Periodically send unit positions */
	if (xea_stats_position_reporting > 0) then {
		(xea_stats_position_reporting) spawn {
			(_this) call xea_fnc_reportUnitPositions;
		};
	};
};
