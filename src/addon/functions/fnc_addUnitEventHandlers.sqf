_this addEventHandler ["fired", {
	_null = _this spawn {
		(_this) call xea_fnc_ehUnitFired;
	};
}];

_this setVariable ["xea_stattrack", true];	// local note that the unit has EHs added
