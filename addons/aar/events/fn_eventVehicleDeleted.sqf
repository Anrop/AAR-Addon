params ["_vehicle"];

private _obj = ["object",
	["type", ["string", "VehicleDeleted"]],
	["vehicle", _vehicle call anrop_aar_fnc_serializeVehicle]
];
_obj call anrop_aar_fnc_sendEvent;
