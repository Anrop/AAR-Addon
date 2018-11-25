params ["_unit"];

private _obj = ["object",
	["type", ["string", "UnitDeleted"]],
	["unit", _unit call anrop_aar_fnc_serializeUnit]
];
_obj call anrop_aar_fnc_sendEvent;
