params ["_unit", "", "", "", "_ammo", "", "_projectile"];

if (isNull _projectile) then {
	_projectile = nearestObject [_unit, _ammo];
};

private _id = format ["%1", _projectile];
private _position = getPosASL _projectile;
private _dir = direction _projectile;
private _side = side _unit;

private _simulation = getText (configFile >> "cfgAmmo" >> typeOf _projectile >> "simulation");

private _arr = ["object",
	["type", ["string", "ProjectileCreated"]],
	["projectile", [_id, ([_position, _dir] call anrop_aar_fnc_serializePosition), _side, _simulation] call anrop_aar_fnc_serializeProjectile],
	["unit", _unit call anrop_aar_fnc_serializeUnit]
];
_arr call anrop_aar_fnc_sendEvent;

[_projectile, _side] spawn anrop_aar_fnc_trackProjectile;
