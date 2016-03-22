params ["_vehicle", "_weapon", "_muzzle", "_mode", "_ammo", "_magazine", "_projectile"];

if (isNull _projectile) then {
	_projectile = nearestObject [_vehicle, _ammo];
};

private "_id";
_id = format ["%1", _projectile];

private "_position";
_position = getPosASL _projectile;

private "_dir";
_dir = direction _projectile;

private "_side";
_side = side _vehicle;

private "_simulation";
_simulation = getText (configFile >> "cfgAmmo" >> typeOf _projectile >> "simulation");

private "_arr";
_arr = ["object",
	["type", ["string", "ProjectileCreated"]],
	["projectile", [_id, ([_position, _dir] call xea_fnc_serializePosition), _side, _simulation] call xea_fnc_serializeProjectile],
	["vehicle", _vehicle call xea_fnc_serializeVehicle]
];
_arr call xea_fnc_sendEvent;

[_projectile, _side] call xea_fnc_trackProjectile;
