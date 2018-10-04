params ["_uid", "_name"];

if (_uid isEqualTo "") exitWith {};

private _player = [_name, _uid] call anrop_aar_fnc_serializePlayer;

private _arr = ["object",
	["type", ["string", "PlayerDisconnected"]],
	["player", _player]
];

_arr call anrop_aar_fnc_sendEvent;
