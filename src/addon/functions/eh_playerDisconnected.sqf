if (not(_this select 0 == "")) then {
	private "_name";
	_name = _this select 1;
	private "_uid";
	_uid = _this select 0;
	private "_player";
	_player = [_name, _uid] call xea_fnc_serializePlayer;

	_arr = ["object",
		["type", ["string", "PlayerDisconnected"]],
		["player", _player]
	];
	_arr call xea_fnc_sendEvent;
};
