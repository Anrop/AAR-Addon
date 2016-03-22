_this addEventHandler ["fired", {
	_null = _this spawn {
		(_this) call xea_fnc_ehVehicleFired;
	};
}];

_this setVariable ["xea_stattrack", true];	// local note that the vehicle has EHs added
