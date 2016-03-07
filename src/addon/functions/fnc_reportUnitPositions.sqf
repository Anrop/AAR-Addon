private "_unitCacheKey";
_unitCacheKey = "stats_unit_cache";

while { true } do {
	{
		private "_name";
		_name = name _x;
		private "_uid";
		_uid = "";
		if (isPlayer _x) then {
			_uid = getPlayerUID _x;
		};
		private "_player";
		_player = [_name, _uid] call xea_fnc_serializePlayer;
		private "_unit";
		_unit = _x call xea_fnc_serializeUnit;

		private "_arr";
		_arr = ["object",
			["type", ["string", "UnitPosition"]],
			["player", _player],
			["unit", _unit]
		];

		private "_cached";
		_cached = _x getVariable _unitCacheKey;

		if (isNil "_cached") then {
			_cached = "";
		};

		private "_serialized";
		_serialized = _arr call xea_fnc_serializeJson;
		if (_serialized != _cached) then {
			_x setVariable [_unitCacheKey, _serialized];
			_serialized call xea_fnc_sendJson;
		};
	} forEach allUnits;
	sleep _this;
};
