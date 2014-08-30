_this addEventHandler ["fired", { (_this) call xea_fnc_ehFired }];
_this addEventHandler ["killed", {(_this) call xea_fnc_ehKilled}];
_this addEventHAndler ["hit", {(_this) call xea_fnc_ehHit}];
_this addEventHandler ["InventoryClosed", {(_this) call xea_fnc_ehInventoryClosed}];
_this setVariable ["xea_stattrack", true];