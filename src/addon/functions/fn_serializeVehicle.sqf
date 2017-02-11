params ["_vehicle"];

private "_id";
_id = netId _vehicle;
private "_name";
_name = getText (configFile >> "CfgVehicles" >> typeOf _vehicle >> "displayName");
private "_position";
_position = ([getPosASL _vehicle, direction _vehicle] call anrop_aar_fnc_serializePosition);
private "_side";
_side = side _vehicle;
private "_simulation";
_simulation = getText (configFile >> "CfgVehicles" >> typeOf _vehicle >> "simulation");

["object",
	["id", ["string", _id]],
	["name", ["string", _name]],
	["position", _position],
	["side", ["string", _side]],
	["simulation", ["string", _simulation]]
];
