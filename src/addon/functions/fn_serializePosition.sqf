params ["_position", "_dir"];

private _x = _position select 0;
private _y = _position select 1;
private _z = _position select 2;

["object",
    ["dir", ["number", _dir]],
    ["x", ["number", _x]],
    ["y", ["number", _y]],
    ["z", ["number", _z]]
];
