/*
////////////////////////////////
// Grab config values and start
////////////////////////////////
_hint = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_civ_hint");
_sleep = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_civ_sleep");
_civradius = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_civ_radius");
_civwaypoints = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_civ_waypoints");
_civdensity = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_civ_density");
_carradius = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_car_radius");
_carwaypoints = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_car_waypoints");
_carnumber = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_car_num");
_squadcas = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_civ_maxsquadcas");
_allcas = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_civ_maxallcas");
_casdisplay = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_civ_casdisplay");
_animalnum = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_animal_max");
_maxradius = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_animal_maxradius");
_minradius = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_animal_minradius");
_boatradius = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_boat_radius");
_boatwaypoints = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_boat_waypoints");
_boatnumber = getnumber(configfile>> "TPW_CIVS_Key_Setting"  >> "tpw_boat_num");
*/

playersToLookup = [];
/*
	TODO:
	Test if eventhandlers are added to JIP players if AI is disabled and thus are newly created
*/

xea_fnc_playerConnected = {
	if (not(_this select 1 == "__SERVER__")) then {
		"testPlugin" callExtension format["event;type=player_connected;id=%1;name=%2", _this select 0, _this select 1];
	};
};

xea_fnc_playerDisconnected = {
	if (not(_this select 1 == "__SERVER__")) then {
		"testPlugin" callExtension format["event;type=player_disconnected;id=%1;name=%2", _this select 0, _this select 1];
	};
};

xea_fnc_event = {
	_str = "";
	for "_i" from 0 to (count _this) -1 do
	{
		_str = _str + format["%1=%2", (_this select _i) select 0, (_this select _i) select 1];
		if (_i < ((count _this) -1)) then {
			_str = _str + ";";
		};
	};	

	diag_log format["sending %1", _str];
	"testPlugin" callExtension format["event;%1", _str];
};

/*
unit: Object - Object the event handler is assigned to 
weapon: String - Fired weapon 
muzzle: String - Muzzle that was used 
mode: String - Current mode of the fired weapon
ammo: String - Ammo used 
magazine: String - magazine name which was used
projectile: Object - Object of the projectile that was shot (Arma 2: OA and onwards)
*/
xea_fnc_ehFired = {
	if(isPlayer (_this select 0)) then {
		_arr = [
			["type", "weapon_fired"],
			["weapon", _this select 1],
			["ammo", _this select 4],
			["id", getPlayerUID (_this select 0)],
			["name", name (_this select 0)]
		];

		_arr call xea_fnc_event;
	};
};

/*
unit: Object - Object the event handler is assigned to 
killer: Object - Object that killed the unit
Contains the unit itself in case of collisions. 
*/
xea_fnc_ehKilled = {
	_killed = [-1, "AI"];
	if (isPlayer (_this select 0)) then {
		_killed = [getPlayerUID (_this select 0), name (_this select 0)];
	};

	_killer = [-1, "AI"];
	if (isPlayer (_this select 1)) then {
		_killer = [getPlayerUID (_this select 1), name (_this select 1)];
	};

	_suicide = false;
	if ((_this select 0) == (_this select 1)) then {
		_suicide = true;
	};
  
	_arr = [
		["type", "unit_killed"],
		["victim_id", _killed select 0],
		["victim_name", _killed select 1],
		//["victim_side", format["%1", side (_this select 0)]],
		["killer_id", _killer select 0],
		["killer_name", _killer select 1],
		["killer_side", format["%1", side (_this select 1)]],
		["suicide", _suicide]
	];

	_arr call xea_fnc_event;
};

/*
unit: Object - Object the event handler is assigned to
container: Object - connected container or weaponholder
*/
xea_fnc_ehInventoryClosed = {
	
};

xea_fnc_missionEnded = {
	
};


["xea_testExtension_connected", "onPlayerConnected", {
	[_uid, _name] call xea_fnc_playerConnected;
}] call BIS_fnc_addStackedEventHandler;

["xea_testExtension_disconnected", "onPlayerDisconnected", {
	[_uid, _name] call xea_fnc_playerDisconnected;
}] call BIS_fnc_addStackedEventHandler;

//addMissionEventHandler ["Ended",(_this) call xea_fnc_missionEnded];


/* Attach various eventhandlers on players */
{
	_x addEventHandler["fired", { (_this) call xea_fnc_ehFired }];
	_x addEventHandler["killed", {(_this) call xea_fnc_ehKilled}];
	_x addEventHandler["InventoryClosed", {(_this) call xea_fnc_ehInventoryClosed}]
} forEach allUnits;

/* Initialize plugin. Get unique ID from server */
"testPlugin" callExtension format["setup;%1", "sigkill.me"];
xea_testPlugin_id = "testPlugin" callExtension format["status;%1", missionName];
