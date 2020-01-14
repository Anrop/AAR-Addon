_this addEventHandler ["deleted", {
	_this call anrop_aar_fnc_eventVehicleDeleted;
}];

_this addEventHandler ["fired", {
	_this call anrop_aar_fnc_eventVehicleFired;
}];

_this setVariable ["anrop_aar", true];	// local note that the vehicle has EHs added
