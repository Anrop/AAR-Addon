_unit = [-1, name (_this select 0)];
if (isPlayer (_this select 0)) then {
	_unit = [getPlayerUID (_this select 0), _unit select 1];
};

_arr = [
	["type", "weapon_fired"],
	["weapon", _this select 1],
	["ammo", _this select 4],
	["uid", _unit select 0],
	["nid", netId (_this select 0)],
	["name", _unit select 1]
];

_arr call xea_fnc_sendEvent;