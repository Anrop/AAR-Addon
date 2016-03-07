// https://community.bistudio.com/wiki/BIS_fnc_MP

/*
_hostname = getString(configFile >> "XEA_STATTRACK_Settings" >> "hostname");
_password = getString(configFile >> "XEA_STATTRACK_Settings" >> "password");
*/
_hostname = "arma-stats.herokuapp.com";
_positionReportDelay = 10;	// Seconds
_positionReporting = true;	// Disabled until delta reporting is implemented to prevent spam
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
	if (_positionReporting) then {
		(_positionReportDelay) spawn {
			(_this) call xea_fnc_reportUnitPositions;
		};
	};
};
