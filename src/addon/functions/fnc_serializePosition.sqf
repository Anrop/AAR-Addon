params ["_unit"];

private "_dir";
_dir = direction _unit;
private "_position";
_position = getPosASL _unit;
private "_x";
_x = _position select 0;
private "_y";
_y = _position select 1;
private "_z";
_z = _position select 2;

["object",
    ["dir", ["number", _dir]],
    ["x", ["number", _x]],
    ["y", ["number", _y]],
    ["z", ["number", _z]]
];
