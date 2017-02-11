private "_unitCacheKey";
_unitCacheKey = "anrop_aar_unit_cache";

while { true } do {
	_reportUnit = {
		private "_name";
		_name = name _x;
		private "_uid";
		_uid = "";
		if (isPlayer _x) then {
			_uid = getPlayerUID _x;
		};
		private "_player";
		_player = [_name, _uid] call anrop_aar_fnc_serializePlayer;
		private "_unit";
		_unit = _x call anrop_aar_fnc_serializeUnit;

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
		_serialized = _arr call anrop_aar_fnc_serializeJson;
		if (_serialized != _cached) then {
			_x setVariable [_unitCacheKey, _serialized];
			_serialized call anrop_aar_fnc_sendJson;
		};
	};

	_reportUnit forEach allUnits;
	_reportUnit forEach allDead;
	sleep _this;
};
