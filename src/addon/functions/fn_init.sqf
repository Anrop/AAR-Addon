// Setup config
anrop_aar_hostname = "arma-stats-api.herokuapp.com";
anrop_aar_position_reporting = 1;
if (isFilePatchingEnabled) then {
	anrop_aar_settings_file = compile preprocessFileLineNumbers "\userconfig\anrop_aar\config.sqf";
	if (!isNil "anrop_aar_settings_file") then {
		[] call anrop_aar_settings_file;
	};
};
anrop_aar_extension = "anrop_aar";	// dll

if (isMultiplayer) then {
	/*
		--------------------------------------------------------------------------------------------------------------
					PLUGIN INIT
	*/

	/* Initialize plugin. Get unique ID from server */
	anrop_aar_extension callExtension format["setup;%1", anrop_aar_hostname];
	private _mission = call anrop_aar_fnc_serializeMission;
	private _missionData = _mission call anrop_aar_fnc_serializeJson;
	anrop_aar_id = anrop_aar_extension callExtension format["mission;%1", _missionData];

	/*
		--------------------------------------------------------------------------------------------------------------
					MISSION INIT
	*/

	/* TODO: check if dedicated creates a dummy user for connection events */
	if (isServer) then {
		["anrop_aar_connected", "onPlayerConnected", {
			[_uid, _name] call anrop_aar_fnc_playerConnected;
		}] call BIS_fnc_addStackedEventHandler;

		["anrop_aar_disconnected", "onPlayerDisconnected", {
			[_uid, _name] call anrop_aar_fnc_playerDisconnected;
		}] call BIS_fnc_addStackedEventHandler;

		addMissionEventHandler ["Ended", { (_this) call anrop_aar_fnc_missionEnded }];
	};

	/*
		--------------------------------------------------------------------------------------------------------------
					UNIT INIT
	*/

	/* Add event handlers to units created during the mission */
	[] spawn {
		while { true } do {
			{
				if !(_x getVariable ["anrop_aar", false]) then {
					_x call anrop_aar_fnc_addUnitEventHandlers;
				};
			} forEach allUnits;

			{
				if !(_x getVariable ["anrop_aar", false]) then {
					_x call anrop_aar_fnc_addVehicleEventHandlers;
				};
			} forEach vehicles;

			sleep 5;
		};
	};

	/* Periodically send unit positions */
	if (anrop_aar_position_reporting > 0) then {
		(anrop_aar_position_reporting) spawn {
			(_this) call anrop_aar_fnc_reportUnitPositions;
		};

		(anrop_aar_position_reporting) spawn {
			(_this) call anrop_aar_fnc_reportVehiclePositions;
		};
	};
};
