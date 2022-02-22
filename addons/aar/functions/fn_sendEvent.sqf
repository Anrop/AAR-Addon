private _serialized = _this call anrop_aar_fnc_serializeJson;
anrop_aar_extension callExtension ["event", [_serialized]];
