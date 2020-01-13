// Setup config
anrop_aar_position_reporting = 1;
anrop_aar_extension = "anrop_aar";	// dll

if (isMultiplayer) then {
	/*
		--------------------------------------------------------------------------------------------------------------
					PLUGIN INIT
	*/

	/* Initialize plugin. Get unique ID from server */
	private _init = anrop_aar_extension callExtension format["init", anrop_aar_hostname];

	if (_init == "ERROR") exitWith {
		diag_log "AAR could not be initialized";
	};

	diag_log format ["AAR initialized: $1", _init];
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
			params ["_uid", "_name"];
			[_uid, _name] call anrop_aar_fnc_playerConnected;
		}] call BIS_fnc_addStackedEventHandler;

		["anrop_aar_disconnected", "onPlayerDisconnected", {
			params ["_uid", "_name"];
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
		[] spawn {
			anrop_aar_position_reporting call anrop_aar_fnc_reportUnitPositions;
		};

		[] spawn {
			anrop_aar_position_reporting call anrop_aar_fnc_reportVehiclePositions;
		};
	};
};
