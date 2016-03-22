params ["_id", "_position", "_simulation", "_side"];

["object",
	["id", ["string", _id]],
	["side", ["string", _side]],
	["simulation", ["string", _simulation]],
	["position", _position]
];
