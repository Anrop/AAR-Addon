/* Initialize functions */
xea_fnc_sendEvent = compile preprocessFile "\xea_armastat\functions\fnc_sendEvent.sqf";
xea_fnc_serializeArray = compile preprocessFile "\xea_armastat\functions\fnc_serializeArray.sqf";
xea_fnc_playerConnected = compile preprocessFile "\xea_armastat\functions\eh_playerConnected.sqf";
xea_fnc_playerDisconnected = compile preprocessFile "\xea_armastat\functions\eh_playerDisconnected.sqf";
xea_fnc_ehFired = compile preprocessFile "\xea_armastat\functions\eh_fired.sqf";
xea_fnc_ehKilled = compile preprocessFile "\xea_armastat\functions\eh_killed.sqf";
xea_fnc_missionEnded = compile preprocessFile "\xea_armastat\functions\eh_missionEnded.sqf";
xea_fnc_ehHit = compile preprocessFile "\xea_armastat\functions\eh_hit.sqf";
xea_fnc_addEventHandlers = compile preprocessFile "\xea_armastat\functions\fnc_addEventHandlers.sqf";
xea_fnc_reportUnitPositions = compile preprocessFile "\xea_armastat\functions\fnc_reportUnitPositions.sqf";