_this addEventHandler ["fired", { (_this) call xea_fnc_ehFired }];
_this addEventHandler ["InventoryClosed", {(_this) call xea_fnc_ehInventoryClosed}];

if (!(_this getVariable["xea_stattrack_mpEvents", false])) then {
	_this setVariable["xea_stattrack_mpEvents", true, true];	// Sync this over network incase more than 1 instance of stattrack is running in the session
	_this addMPEventHandler ["MPKilled", {(_this) call xea_fnc_ehKilled}];
	_this addMPEventHAndler ["MPHit", {(_this) call xea_fnc_ehHit}];
};

_this setVariable ["xea_stattrack", true];	// local note that the unit has EHs added