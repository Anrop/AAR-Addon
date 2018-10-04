params ["_unit"];

private _id = netId _unit;
private _lifeState = lifeState _unit;
private _name = name _unit;
private _position = ([getPosASL _unit, direction _unit] call anrop_aar_fnc_serializePosition);
private _side = side _unit;

private "_arr";
_arr = ["object",
	["id", ["string", _id]],
	["life_state", ["string", _lifeState]],
	["name", ["string", _name]],
	["position", _position],
	["side", ["string", _side]]
];

if (vehicle _unit != _unit) then {
	private _vehicleId = netId vehicle _unit;
	_arr pushBack ["vehicle_id", ["string", _vehicleId]];
};

_arr;
