params ["_vehicle"];

private _id = netId _vehicle;
private _name = getText (configFile >> "CfgVehicles" >> typeOf _vehicle >> "displayName");
private _dir = direction _vehicle;
(getPosASL _vehicle) params ["_posX", "_posY", "_posZ"];
private _side = str side _vehicle;
private _simulation = getText (configFile >> "CfgVehicles" >> typeOf _vehicle >> "simulation");

anrop_aar_extension callExtension ["vehiclePosition", [_id, _name, _dir, _posX, _posY, _posZ, _side, _simulation]];
