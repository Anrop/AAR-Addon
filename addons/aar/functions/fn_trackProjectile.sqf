params ["_projectile", "_side"];

private _id = format ["%1", _projectile];
private _position = getPosASL _projectile;
private _dir = direction _projectile;

private _simulation = getText (configFile >> "cfgAmmo" >> typeOf _projectile >> "simulation");

private _lastTime = time;

waitUntil {
	if !(isNull _projectile) then {
		_dir = direction _projectile;
		_position = getPosASL _projectile;

		if (time >= (_lastTime + 1)) then {
			_lastTime = time;

			[_id, _position, _dir, _simulation, _side] spawn {
				params ["_id", "_position", "_dir", "_simulation", "_side"];

				private _arr = ["object",
					["type", ["string", "ProjectilePosition"]],
					["projectile", [_id, ([_position, _dir] call anrop_aar_fnc_serializePosition), _side, _simulation] call anrop_aar_fnc_serializeProjectile]
				];
				_arr call anrop_aar_fnc_sendEvent;
			};
		};
	};

	isNull _projectile;
};

private _arr = ["object",
	["type", ["string", "ProjectileDestroyed"]],
	["projectile", [_id, ([_position, _dir] call anrop_aar_fnc_serializePosition), _side, _simulation] call anrop_aar_fnc_serializeProjectile]
];
_arr call anrop_aar_fnc_sendEvent;
