private "_serialized";
_serialized = _this call xea_fnc_serializeJson;
xea_extension callExtension format["event;%1", _serialized];
