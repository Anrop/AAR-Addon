private "_unitCacheKey";
_unitCacheKey = "anrop_aar_unit_cache";

while { true } do {
	private _reportUnit = {
		params ["_reportedUnit"];

		private _name = _reportedUnit call anrop_aar_fnc_getUnitName;
		private _uid = "";
		if (isPlayer _reportedUnit) then {
			_uid = getPlayerUID _reportedUnit;
		};
		private _player = [_name, _uid] call anrop_aar_fnc_serializePlayer;
		private _unit = _reportedUnit call anrop_aar_fnc_serializeUnit;

		private _arr = ["object",
			["type", ["string", "UnitPosition"]],
			["player", _player],
			["unit", _unit]
		];

		private _cached = _reportedUnit getVariable [_unitCacheKey, ""];

		private _serialized = _arr call anrop_aar_fnc_serializeJson;
		if (_serialized != _cached) then {
			_reportedUnit setVariable [_unitCacheKey, _serialized];
			_serialized call anrop_aar_fnc_sendJson;
		};
	};

	private _allUnits = allUnits;
	_allUnits append allDead;

	{
		[_x] call _reportUnit;
	} forEach _allUnits;

	sleep _this;
};
