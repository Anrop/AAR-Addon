private "_vehicleCacheKey";
_vehicleCacheKey = "anrop_aar_vehicle_cache";

while { true } do {
	private _reportVehicle = {
		params ["_reportedVehicle"];

		private _vehicle = _reportedVehicle call anrop_aar_fnc_serializeVehicle;

		private "_arr";
		_arr = ["object",
			["type", ["string", "VehiclePosition"]],
			["vehicle", _vehicle]
		];

		private _cached = _reportedVehicle getVariable [_vehicleCacheKey, ""];;

		private _serialized = _arr call anrop_aar_fnc_serializeJson;
		if (_serialized != _cached) then {
			_reportedVehicle setVariable [_vehicleCacheKey, _serialized];
			_serialized call anrop_aar_fnc_sendJson;
		};
	};

	{
		_x call _reportVehicle
	} forEach vehicles;
	sleep _this;
};
