_str = "";
for "_i" from 0 to (count _this) -1 do
{
	_str = _str + format["%1=%2", (_this select _i) select 0, (_this select _i) select 1];
	if (_i < ((count _this) -1)) then {
		_str = _str + ";";
	};
};

_str