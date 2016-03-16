private "_vehicleCacheKey";
_vehicleCacheKey = "stats_vehicle_cache";

while { true } do {
	_reportVehicle = {
		private "_vehicle";
		_vehicle = _x call xea_fnc_serializeVehicle;

		private "_arr";
		_arr = ["object",
			["type", ["string", "VehiclePosition"]],
			["vehicle", _vehicle]
		];

		private "_cached";
		_cached = _x getVariable _vehicleCacheKey;

		if (isNil "_cached") then {
			_cached = "";
		};

		private "_serialized";
		_serialized = _arr call xea_fnc_serializeJson;
		if (_serialized != _cached) then {
			_x setVariable [_vehicleCacheKey, _serialized];
			_serialized call xea_fnc_sendJson;
		};
	};

	_reportVehicle forEach vehicles;
	sleep _this;
};
