params ["_position", "_dir"];

_position params ["_x", "_y", "_z"];

["object",
    ["dir", ["number", _dir]],
    ["x", ["number", _x]],
    ["y", ["number", _y]],
    ["z", ["number", _z]]
];
