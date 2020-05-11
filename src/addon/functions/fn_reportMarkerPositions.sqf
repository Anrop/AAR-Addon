private _markerHash = [[], ""] call CBA_fnc_hashCreate;
private _currentMarkers = [];

private _reportMarker = {
	params ["_event", "_marker"];

	private _serializedMarker = _marker call anrop_aar_fnc_serializeMarker;

	private _obj = ["object",
		["type", ["string", _event]],
		["marker", _serializedMarker]
	];

	private _cached = [_markerHash, _marker] call CBA_fnc_hashGet;

	private _serialized = _obj call anrop_aar_fnc_serializeJson;
	if (_serialized != _cached) then {
		[_markerHash, _marker, _serialized] call CBA_fnc_hashSet;
		_serialized call anrop_aar_fnc_sendJson;
	};
};

while { true } do {
	private _allMarkers = allMapMarkers;
	private _newMarkers = _allMarkers - _currentMarkers;
	private _updatedMarkers = _allMarkers - _newMarkers;
	private _removedMarkers = _currentMarkers - _allMarkers;

	{
		["MarkerCreated", _x] call _reportMarker;
	} forEach _newMarkers;

	{
		["MarkerPosition", _x] call _reportMarker;
	} forEach _updatedMarkers;

	{
		["MarkerDeleted", _x] call _reportMarker;
	} forEach _removedMarkers;

	sleep _this;
};
