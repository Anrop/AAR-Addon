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

		_arr call xea_fnc_sendEvent;
	} forEach allUnits;
	sleep _this;
};
