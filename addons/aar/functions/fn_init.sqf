// Setup config
anrop_aar_position_reporting = 1;
anrop_aar_extension = "anrop_aar";

if (!isMultiplayer) exitWith {
	diag_log "[Anrop AAR] only enabled with multiplayer";
};

if (!isServer) exitWith {
	diag_log "[Anrop AAR] only enabled for server";
};

// Initialize plugin. Get unique ID from server
private _init = anrop_aar_extension callExtension format["init"];

if (_init == "") exitWith {
	diag_log "[Anrop AAR] extension could not be found";
};

if (_init == "ERROR") exitWith {
	diag_log "[Anrop AAR] error during init";
};

diag_log format ["[Anrop AAR] initialized: %1", _init];

private _mission = call anrop_aar_fnc_serializeMission;
private _missionData = _mission call anrop_aar_fnc_serializeJson;
anrop_aar_id = anrop_aar_extension callExtension format["mission;%1", _missionData];
diag_log format ["[Anrop AAR] mission id: %1", anrop_aar_id];

// Add mission events
["anrop_aar_connected", "onPlayerConnected", {
	params ["_uid", "_name"];
	[_uid, _name] call anrop_aar_fnc_playerConnected;
}] call BIS_fnc_addStackedEventHandler;

["anrop_aar_disconnected", "onPlayerDisconnected", {
	params ["_uid", "_name"];
	[_uid, _name] call anrop_aar_fnc_playerDisconnected;
}] call BIS_fnc_addStackedEventHandler;

addMissionEventHandler ["Ended", { (_this) call anrop_aar_fnc_missionEnded }];

// Add event handlers to units created during the mission
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

// Periodically send unit positions
if (anrop_aar_position_reporting > 0) then {
	[] spawn {
		anrop_aar_position_reporting call anrop_aar_fnc_reportUnitPositions;
	};

	[] spawn {
		anrop_aar_position_reporting call anrop_aar_fnc_reportVehiclePositions;
	};
};
