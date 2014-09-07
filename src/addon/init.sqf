// https://community.bistudio.com/wiki/BIS_fnc_MP

/*
_hostname = getString(configFile >> "XEA_STATTRACK_Settings" >> "hostname");
_password = getString(configFile >> "XEA_STATTRACK_Settings" >> "password");
*/
_hostname = "armastats.sigkill.me";
_positionReportDelay = 1;	// Minutes
_positionReporting = true;
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
	xea_extension callExtension format["setup;%1", _hostname];
	xea_stattrack_id = xea_extension callExtension format["status;%1", missionName];

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

	} else {
		/* Not server. attempt to inject functions to the server to broadcast CBA events (assumes server has cba) */
		["xea_armastat_playerConnected", {
			_this call xea_fnc_playerConnected;
		}] call CBA_fnc_addEventHandler;

		["xea_armastat_playerDisconnected", {
			_this call xea_fnc_playerDisconnected;
		}] call CBA_fnc_addEventHandler;

		["xea_armastat_missionEnded", {
			_this call xea_fnc_missionEnded;
		}] call CBA_fnc_addEventHandler;

		xea_fnc_armastat_injectedHandler = {
			if (isNil "xea_armastat_hasInjectedHandler") then {
				xea_armastat_hasInjectedHandler = true;

				["xea_armastat_connected", "onPlayerConnected", {
					["xea_armastat_playerConnected", [_uid, _name]] call CBA_fnc_globalEvent; 
				}] call BIS_fnc_addStackedEventHandler;
				["xea_armastat_disconnected", "onPlayerDisconnected", {
					["xea_armastat_playerDisconnected", [_uid, _name]] call CBA_fnc_globalEvent; 
				}] call BIS_fnc_addStackedEventHandler;

				addMissionEventHandler ["Ended", { ["xea_armastat_missionEnded" ,_this] call CBA_fnc_globalEvent; }];
			};
		};

		[xea_fnc_armastat_injectedHandler,"BIS_fnc_spawn",false,false] call BIS_fnc_MP;
	};

	/*
		--------------------------------------------------------------------------------------------------------------
					UNIT INIT
	*/

	/* Attach various eventhandlers on players */
	{
		_x call xea_fnc_addEventHandlers;
	} forEach allUnits;

	/* Add event handlers to units created during the mission */
	[] spawn {
		while { true } do {
			{
				if (!(_x getVariable ["xea_stattrack", false])) then {
					_x call xea_fnc_addEventHandlers;
				};
			} foreach allUnits;
			sleep 5;
		};
	};

	/* Periodically send unit positions */
	if (_positionReporting) then {
		(_positionReportDelay) spawn {
			(_this*60) call xea_fnc_reportUnitPositions;
		};
	};
};