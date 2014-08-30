_killed = [-1, "AI"];
if (isPlayer (_this select 0)) then {
	_killed = [getPlayerUID (_this select 0), name (_this select 0)];
};

_killer = [-1, "AI"];
if (isPlayer (_this select 1)) then {
	_killer = [getPlayerUID (_this select 1), name (_this select 1)];
};

_suicide = false;
if ((_this select 0) == (_this select 1)) then {
	_suicide = true;
};

_arr = [
	["type", "unit_killed"],
	["victim_id", _killed select 0],
	["victim_name", _killed select 1],
	//["victim_side", format["%1", side (_this select 0)]],
	["killer_id", _killer select 0],
	["killer_name", _killer select 1],
	["killer_side", format["%1", side (_this select 1)]],
	["suicide", _suicide]
];

_arr call xea_fnc_event;
