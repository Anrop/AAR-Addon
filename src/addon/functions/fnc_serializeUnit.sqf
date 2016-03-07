params ["_unit"];

private "_id";
_id = netId _unit;
private "_name";
_name = name _unit;
private "_position";
_position = (_unit call xea_fnc_serializePosition);
private "_side";
_side = side _unit;

["object",
	["id", ["string", _id]],
	["name", ["string", _name]],
	["position", _position],
	["side", ["string", _side]]
];
