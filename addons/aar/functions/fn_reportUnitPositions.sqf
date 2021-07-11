private _allUnits = allUnits;
_allUnits append allDead;

{
	[_x] call anrop_aar_fnc_sendUnitPosition;
} forEach _allUnits;
