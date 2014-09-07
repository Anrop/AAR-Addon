while { true } do {
	{
		_unit = [-1, name _x];
		if (isPlayer _x) then {
			_unit = [getPlayerUID _x, _unit select 1];
		};

		_arr = [
			["type", "unit_position"],
			["posX", (getPosASL _x select 0)],
			["posY", (getPosASL _x select 1)],
			["posZ", (getPosASL _x select 2)],
			["nid", netId _x],
			["uid", _unit select 0],
			["name", _unit select 1]
		];

		_arr call xea_fnc_sendEvent;

	} forEach allUnits;
	sleep _this;
};