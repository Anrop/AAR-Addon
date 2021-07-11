params ["_projectile", "_side"];

private _id = format ["%1", _projectile];
private _simulation = getText (configFile >> "cfgAmmo" >> typeOf _projectile >> "simulation");

[{
	params ["_args", "_handle"];
    _args params ["_projectile", "_id", "_side", "_simulation"];

	if (isNull _projectile) exitWith {
		_handle call CBA_fnc_removePerFrameHandler;
	};

	_dir = direction _projectile;
	_position = getPosASL _projectile;

	private _arr = ["object",
		["type", ["string", "ProjectilePosition"]],
		["projectile", [_id, ([_position, _dir] call anrop_aar_fnc_serializePosition), _side, _simulation] call anrop_aar_fnc_serializeProjectile]
	];
	_arr call anrop_aar_fnc_sendEvent;
}, 1, [_projectile, _id, _side, _simulation]] call CBA_fnc_addPerFrameHandler;
