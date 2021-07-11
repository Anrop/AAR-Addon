params ["_unit"];

private _id = netId _unit;
private _lifeState = lifeState _unit;
private _name = _unit call anrop_aar_fnc_getUnitName;
private _dir = direction _unit;
(getPosASL _unit) params ["_posX", "_posY", "_posZ"];
private _side = side _unit;

private _uid = "";
if (isPlayer _unit) then {
	_uid = getPlayerUID _unit;
};

private _vehicleId = "";
if (vehicle _unit != _unit) then {
	_vehicleId = netId vehicle _unit;
};

anrop_aar_extension callExtension ["unitPosition", [_id, _lifeState, _name, _dir, _posX, _posY, _posZ, _side, _uid, _vehicleId]];

