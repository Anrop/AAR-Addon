while { true } do {
	{
		_unit = [-1, name _x];
		if (isPlayer _x) then {
			_unit = [getPlayerUID _x, _unit select 1];
		};

		_arr = [
			["type", "unit_position"],
			["pos_x", _this select 1],
			["pos_y", _this select 4],
			["pos_z", _unit select 0],
			["nid", netId (_this select 0)],
			["uid", ],
			["name", _unit select 1]
		];

	} forEach allUnits;
	sleep 30;
};