params ["_unit"];

// Check if unit name is already known by ACE mod
private _name = _unit getVariable ["ACE_Name", ""];

if (_name != "") exitWith { _name };

// Update name if unit is alive
if (alive _unit) exitWith {
  _name = name _unit;
  _unit setVariable ["anrop_aar_unit_name", _name];
  _name
};

// Try to use name saved by AAR when unit was last alive
_name = _unit getVariable ["anrop_aar_unit_name", ""];
if (_name != "") exitWith { _name };

_name = name _unit;
_unit setVariable ["anrop_aar_unit_name", _name];
_name
