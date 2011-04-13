/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef MAPLOCATIONTYPE_H_
#define MAPLOCATIONTYPE_H_

class MapLocationType {
public:

	static const int UNKNOWN = 1;
	static const int BANK = 2;
	static const int CANTINA = 3;
	static const int CAPITOL = 4;
	static const int CLONING_FACILITY = 5;
	static const int PARKING_GARAGE = 6;

	static const int GUILD_HALL = 7;
	static const int GUILD_COMBAT = 8;
	static const int GUILD_COMMERCE = 9;
	static const int GUILD_THEATER = 10;
	static const int GUILD_UNIVERSITY = 11;

	static const int HOTEL = 12;
	static const int MEDICAL_CENTER = 13;
	static const int SHUTTLEPORT = 14;
	static const int STARPORT = 15;
	static const int THEME_PARK = 16;
	static const int CITY = 17;
	static const int INVISIBLE = 18;

	static const int TRAINER = 19;
	static const int TRAINER_BRAWLER = 20;
	static const int TRAINER_ARTISAN = 21;
	static const int TRAINER_SCOUT = 22;
	static const int TRAINER_MARKSMAN = 23;
	static const int TRAINER_ENTERTAINER = 24;
	static const int TRAINER_MEDIC = 25;
	static const int TRAINER_STARFIGHTER_ENGINEER_TRAINER = 62;
	static const int TRAINER_SHIPWRIGHT = 63;
	static const int TRAINER_PRIVATEER_PILOT = 64;
	static const int TRAINER_REBEL_PILOT = 65;
	static const int TRAINER_IMPERIAL_PILOT = 66;

	static const int JUNK_SHOP = 26;
	static const int TAVERN = 27;
	static const int BARRACKS = 28;

	static const int VENDOR = 29;
	static const int VENDOR_ARMOR = 30;
	static const int VENDOR_CLOTHING = 31;
	static const int VENDOR_COMPONENTS = 32;
	static const int VENDOR_DROIDS = 33;
	static const int VENDOR_EQUIPMENT = 34;
	static const int VENDOR_FOOD = 35;
	static const int VENDOR_HOUSING = 36;
	static const int VENDOR_RESOURCES = 37;
	static const int VENDOR_TOOLS = 38;
	static const int VENDOR_WEAPONS = 39;
	static const int VENDOR_JUNK = 40;
	static const int VENDOR_PETS = 52;
	static const int VENDOR_MEDICAL_SUPPLIES = 53;

	static const int TERMINAL = 41;
	static const int TERMINAL_BANK = 42;
	static const int TERMINAL_BAZAAR = 43;
	static const int TERMINAL_MISSION = 44;

	static const int REBEL = 45;
	static const int REBEL_HEADQUARTERS = 47;

	static const int IMPERIAL = 46;
	static const int IMPERIAL_HEADQUARTERS = 48;

	static const int CAMP = 49;
	static const int CITY_HALL = 50;
	static const int PLAYER_THEATER = 51;
	static const int PLAYER_INVISIBLE = 54;
	static const int PLAYER_PARKING_GARAGE = 55;
	static const int MUSEUM = 56;
	static const int SALON = 57;

	static const int SPACE = 58;
	static const int SPACE_RECRUITER = 59;
	static const int SPACE_STARSHIP_CHASSIS_BROKER = 60;
	static const int SPACE_STARSHIP_CHASSIS = 61; // ??
	static const int SPACE_SHIPS = 67; // ??


	static String getMapLocationName(uint8 maptype) {
		String name = "";

		switch (maptype) {

		case UNKNOWN:
			name = "@map_loc_cat_n:unknown";
			break;
		case BANK:
			name = "@map_loc_cat_n:bank";
			break;
		case CANTINA:
			name = "@map_loc_cat_n:cantina";
			break;
		case CAPITOL:
			name = "@map_loc_cat_n:capitol";
			break;
		case CLONING_FACILITY:
			name = "@map_loc_cat_n:cloningfacility";
			break;
		case PARKING_GARAGE:
			name = "@map_loc_cat_n:garage";
			break;
		case GUILD_HALL:
			name = "@map_loc_cat_n:guild";
			break;
		case GUILD_COMBAT:
			name = "@map_loc_cat_n:guild_combat";
			break;
		case GUILD_COMMERCE:
			name = "@map_loc_cat_n:guild_commerce";
			break;
		case GUILD_THEATER:
			name = "@map_loc_cat_n:guild_theater";
			break;
		case GUILD_UNIVERSITY:
			name = "@map_loc_cat_n:guild_university";
			break;
		case HOTEL:
			name = "@map_loc_cat_n:hotel";
			break;
		case MEDICAL_CENTER:
			name = "@map_loc_cat_n:medicalcenter";
			break;
		case SHUTTLEPORT:
			name = "@map_loc_cat_n:shuttleport";
			break;
		case STARPORT:
			name = "@map_loc_cat_n:starport";
			break;
		case THEME_PARK:
			name = "@map_loc_cat_n:themepark";
			break;
		case CITY:
			name = "@map_loc_cat_n:city";
			break;
		case INVISIBLE:
			name = "@map_loc_cat_n:other";
			break;
		case TRAINER:
			name = "@map_loc_cat_n:trainer";
			break;
		case TRAINER_BRAWLER:
			name = "@map_loc_cat_n:trainer_brawler";
			break;
		case TRAINER_ARTISAN:
			name = "@map_loc_cat_n:trainer_artisan";
			break;
		case TRAINER_SCOUT:
			name = "@map_loc_cat_n:trainer_scout";
			break;
		case TRAINER_MARKSMAN:
			name = "@map_loc_cat_n:trainer_marksman";
			break;
		case TRAINER_ENTERTAINER:
			name = "@map_loc_cat_n:trainer_entertainer";
			break;
		case TRAINER_MEDIC:
			name = "@map_loc_cat_n:trainer_medic";
			break;
		case TRAINER_STARFIGHTER_ENGINEER_TRAINER:
			name = "@map_loc_cat_n:trainer_starfighter_engineer";
			break;
		case TRAINER_SHIPWRIGHT:
			name = "@map_loc_cat_n:trainer_shipwright";
			break;
		case TRAINER_PRIVATEER_PILOT:
			name = "@find_display:trainer_pilot_privateer";
			break;
		case TRAINER_REBEL_PILOT:
			name = "@map_loc_cat_n:trainer_pilot_rebel";
			break;
		case TRAINER_IMPERIAL_PILOT:
			name = "@map_loc_cat_n:trainer_pilot_imperial";
			break;
		case JUNK_SHOP:
			name = "@map_loc_cat_n:junkshop";
			break;
		case TAVERN:
			name = "@map_loc_cat_n:tavern";
			break;
		case BARRACKS:
			name = "@map_loc_cat_n:barracks";
			break;
		case VENDOR:
			name = "@map_loc_cat_n:vendor";
			break;
		case VENDOR_JUNK:
			name = "@map_loc_cat_n:vendor_junk";
			break;
		case VENDOR_ARMOR:
			name = "@map_loc_cat_n:vendor_armor";
			break;
		case VENDOR_CLOTHING:
			name = "@map_loc_cat_n:vendor_clothing";
			break;
		case VENDOR_COMPONENTS:
			name = "@map_loc_cat_n:vendor_components";
			break;
		case VENDOR_DROIDS:
			name = "@map_loc_cat_n:vendor_droids";
			break;
		case VENDOR_EQUIPMENT:
			name = "@map_loc_cat_n:vendor_equipment";
			break;
		case VENDOR_FOOD:
			name = "@map_loc_cat_n:vendor_food";
			break;
		case VENDOR_HOUSING:
			name = "@map_loc_cat_n:vendor_housing";
			break;
		case VENDOR_RESOURCES:
			name = "@map_loc_cat_n:vendor_resources";
			break;
		case VENDOR_TOOLS:
			name = "@map_loc_cat_n:vendor_tools";
			break;
		case VENDOR_WEAPONS:
			name = "@map_loc_cat_n:vendor_weapons";
			break;
		case VENDOR_PETS:
			name = "@map_loc_cat_n:vendor_pets";
			break;
		case VENDOR_MEDICAL_SUPPLIES:
			name = "@map_loc_cat_n:vendor_medical";
			break;
		case TERMINAL:
			name = "@map_loc_cat_n:terminal";
			break;
		case TERMINAL_BANK:
			name = "@map_loc_cat_n:terminal_bank";
			break;
		case TERMINAL_BAZAAR:
			name = "@map_loc_cat_n:terminal_bazaar";
			break;
		case TERMINAL_MISSION:
			name = "@map_loc_cat_n:terminal_mission";
			break;
		case REBEL:
			name = "@map_loc_cat_n:rebel";
			break;
		case REBEL_HEADQUARTERS:
			name = "@map_loc_cat_n:rebel_hq";
			break;
		case IMPERIAL:
			name = "@map_loc_cat_n:imperial";
			break;
		case IMPERIAL_HEADQUARTERS:
			name = "@map_loc_cat_n:imperial_hq";
			break;
		case CAMP:
			name = "@map_loc_cat_n:camp";
			break;
		case CITY_HALL:
			name = "@map_loc_cat_n:cityhall";
			break;
		case PLAYER_THEATER:
			name = "@map_loc_cat_n:theater";
			break;
		case PLAYER_PARKING_GARAGE:
			name = "@map_loc_cat_n:garage";
			break;
		case PLAYER_INVISIBLE:
			name = "@map_loc_cat_n:other";
			break;
		case MUSEUM:
			name = "@map_loc_cat_n:museum";
			break;
		case SALON:
			name = "@map_loc_cat_n:salon";
			break;
		default:
			name = "@map_loc_cat_n:other";
			break;

		}

		return name;

	}

};

#endif /*MapLocationType_H_*/
