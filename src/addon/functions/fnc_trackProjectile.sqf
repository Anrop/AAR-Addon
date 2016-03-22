params ["_projectile", "_side"];

private "_id";
_id = format ["%1", _projectile];

private "_position";
_position = getPosASL _projectile;

private "_dir";
_dir = direction _projectile;

private "_simulation";
_simulation = getText (configFile >> "cfgAmmo" >> typeOf _projectile >> "simulation");

private "_lastTime";
_lastTime = time;

waitUntil {
	if (not isNull _projectile) then {
		_dir = direction _projectile;
		_position = getPosASL _projectile;

		if (time >= (_lastTime + 1)) then {
			_lastTime = time;

			[_id, _position, _dir, _simulation, _side] spawn {
				params ["_id", "_position", "_dir", "_simulation", "_side"];

				_arr = ["object",
					["type", ["string", "ProjectilePosition"]],
					["projectile", [_id, ([_position, _dir] call xea_fnc_serializePosition), _simulation, _side] call xea_fnc_serializeProjectile]
				];
				_arr call xea_fnc_sendEvent;
			};
		};
	};

	isNull _projectile;
};

_arr = ["object",
	["type", ["string", "ProjectileDestroyed"]],
	["projectile", [_id, ([_position, _dir] call xea_fnc_serializePosition), _simulation, _side] call xea_fnc_serializeProjectile]
];
_arr call xea_fnc_sendEvent;
