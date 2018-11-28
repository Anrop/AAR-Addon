params ["_marker"];

private _id = _marker;
private _alpha = markerAlpha _marker;
private _brush = markerBrush _marker;
private _color = markerColor _marker;
private _position = ([markerPos _marker, markerDir _marker] call anrop_aar_fnc_serializePosition);
private _shape = markerShape _marker;
private _size = markerSize _marker;
private _text = markerText _marker;
private _type = markerType _marker;

["object",
	["id", ["string", _id]],
	["alpha", ["number", _alpha]],
	["brush", ["string", _brush]],
	["color", ["string", _color]],
	["position", _position],
	["shape", ["string", _shape]],
	["size", ["object",
	    ["width", ["number", _size select 0]],
	    ["height", ["number", _size select 1]]
	]],
	["text", ["string", _text]],
	["type", ["string", _type]]
];
