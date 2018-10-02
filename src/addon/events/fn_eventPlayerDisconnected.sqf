
if ((_this select 0) isEqualTo "") exitWith {};

private _name = _this select 1;
private _uid = _this select 0;
private _player = [_name, _uid] call anrop_aar_fnc_serializePlayer;

private _arr = ["object",
	["type", ["string", "PlayerDisconnected"]],
	["player", _player]
];
_arr call anrop_aar_fnc_sendEvent;
