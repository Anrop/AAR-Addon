params ["_vehicle", "", "", "", "_ammo", "", "_projectile"];

if (isNull _projectile) then {
	_projectile = nearestObject [_vehicle, _ammo];
};

private _id = format ["%1", _projectile];
private _position = getPosASL _projectile;
private _dir = direction _projectile;
private _side = side _vehicle;
private _simulation = getText (configFile >> "cfgAmmo" >> typeOf _projectile >> "simulation");

private _arr = ["object",
	["type", ["string", "ProjectileCreated"]],
	["projectile", [_id, ([_position, _dir] call anrop_aar_fnc_serializePosition), _side, _simulation] call anrop_aar_fnc_serializeProjectile],
	["vehicle", _vehicle call anrop_aar_fnc_serializeVehicle]
];
_arr call anrop_aar_fnc_sendEvent;

[_projectile, _side] call anrop_aar_fnc_trackProjectile;
