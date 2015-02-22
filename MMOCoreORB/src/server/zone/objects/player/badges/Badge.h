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

#ifndef BADGE_H_
#define BADGE_H_

#include "engine/engine.h"

class Badge {
	static uint8 types[];
	static String names[];

public:
	//First Bitmask
	enum {
		COUNT_5 = 0,
		COUNT_10 = 1,
		COUNT_25 = 2,
		COUNT_50 = 3,
		COUNT_75 = 4,
		COUNT_100 = 5,
		COUNT_125 = 6,
		POI_RABIDBEAST = 7,
		POI_PRISONBREAK = 8,
		POI_TWOLIARS = 9,
		POI_FACTORYLIBERATION = 10,
		POI_HEROMARK = 11,
		EXP_TAT_BENS_HUT = 12,
		EXP_TAT_TUSKEN_POOL = 13,
		EXP_TAT_KRAYT_SKELETON = 14,
		EXP_TAT_ESCAPE_POD = 15,
		EXP_TAT_SARLACC_PIT = 16,
		EXP_TAT_LARS_HOMESTEAD = 17,
		EXP_TAT_KRAYT_GRAVEYARD = 18,
		EXP_NAB_GUNGAN_SACRED_PLACE = 19,
		EXP_COR_AGRILAT_SWAMP = 20,
		EXP_YAV_TEMPLE_WOOLAMANDER = 21,
		EXP_YAV_TEMPLE_BLUELEAF = 22,
		EXP_YAV_TEMPLE_EXAR_KUN = 23,
		EXP_LOK_VOLCANO = 24,
		EXP_DAT_TARPIT = 25,
		EXP_DAT_SARLACC = 26,
		EXP_DAT_ESCAPE_POD = 27,
		EXP_DAT_MISTY_FALLS_1 = 28,
		EXP_DAT_MISTY_FALLS_2 = 29,
		EXP_DAN_JEDI_TEMPLE = 30,
		EXP_DAN_REBEL_BASE = 31
	};

	//Second Bitmask
	enum {
		EVENT_PROJECT_DEAD_EYE_1 = 32,
		ACC_GOOD_SAMARITAN = 33,
		ACC_FASCINATING_BACKGROUND = 34,
		ACC_BRAVE_SOLDIER = 35,
		ACC_INTERESTING_PERSONAGE = 36,
		ACC_PROFESSIONAL_DEMEANOR = 37,
		WARREN_COMPASSION = 38,
		WARREN_HERO = 39,
		EVENT_COA2_REBEL = 40,
		EVENT_COA2_IMPERIAL = 41,
		COMBAT_1HSWORD_MASTER = 42,
		COMBAT_2HSWORD_MASTER = 43,
		COMBAT_BOUNTYHUNTER_MASTER = 44,
		COMBAT_BRAWLER_MASTER = 45,
		COMBAT_CARBINE_MASTER = 46,
		COMBAT_COMMANDO_MASTER = 47,
		COMBAT_MARKSMAN_MASTER = 48,
		COMBAT_PISTOL_MASTER = 49,
		COMBAT_POLEARM_MASTER = 50,
		COMBAT_RIFLEMAN_MASTER = 51,
		COMBAT_SMUGGLER_MASTER = 52,
		COMBAT_UNARMED_MASTER = 53,
		CRAFTING_ARCHITECT_MASTER = 54,
		CRAFTING_ARMORSMITH_MASTER = 55,
		CRAFTING_ARTISAN_MASTER = 56,
		CRAFTING_CHEF_MASTER = 57,
		CRAFTING_DROIDENGINEER_MASTER = 58,
		CRAFTING_MERCHANT_MASTER = 59,
		CRAFTING_TAILOR_MASTER = 60,
		CRAFTING_WEAPONSMITH_MASTER = 61,
		OUTDOORS_BIOENGINEER_MASTER = 62,
		OUTDOORS_CREATUREHANDLER_MASTER = 63
	};

	//Third Bitmask
	enum {
		OUTDOORS_RANGER_MASTER = 64,
		OUTDOORS_SCOUT_MASTER = 65,
		OUTDOORS_SQUADLEADER_MASTER = 66,
		SCIENCE_COMBATMEDIC_MASTER = 67,
		SCIENCE_DOCTOR_MASTER = 68,
		SCIENCE_MEDIC_MASTER = 69,
		SOCIAL_DANCER_MASTER = 70,
		SOCIAL_ENTERTAINER_MASTER = 71,
		SOCIAL_IMAGEDESIGNER_MASTER = 72,
		SOCIAL_MUSICIAN_MASTER = 73,
		SOCIAL_POLITICIAN_MASTER = 74,
		BDG_EXP_NAB_THEED_FALLS_BOTTOM = 75,
		BDG_EXP_NAB_DEEJA_FALLS_TOP = 76,
		BDG_EXP_NAB_AMIDALAS_SANDY_BEACH = 77,
		BDG_EXP_COR_REBEL_HIDEOUT = 78,
		BDG_EXP_COR_ROGUE_CORSEC_BASE = 79,
		BDG_EXP_COR_TYRENA_THEATER = 80,
		BDG_EXP_COR_BELA_VISTAL_FOUNTAIN = 81,
		BDG_EXP_DAT_CRASHED_SHIP = 82,
		BDG_EXP_DAT_IMP_PRISON = 83,
		BDG_EXP_DAN_DANTARI_VILLAGE1 = 84,
		BDG_EXP_DAN_DANTARI_VILLAGE2 = 85,
		BDG_EXP_END_EWOK_TREE_VILLAGE = 86,
		BDG_EXP_END_EWOK_LAKE_VILLAGE = 87,
		BDG_EXP_END_DULOK_VILLAGE = 88,
		BDG_EXP_END_IMP_OUTPOST = 89,
		BDG_EXP_TAL_CREATURE_VILLAGE = 90,
		BDG_EXP_TAL_IMP_BASE = 91,
		BDG_EXP_TAL_IMP_VS_REB_BATTLE = 92,
		BDG_EXP_TAL_AQUALISH_CAVE = 93,
		BDG_EXP_ROR_KOBALA_SPICE_MINE = 94,
		BDG_EXP_ROR_REBEL_OUTPOST = 95
	};

	//Fourth Bitmask
	enum {
		BDG_EXP_ROR_IMP_CAMP = 96,
		BDG_EXP_ROR_IMP_HYPERDRIVE_FAC = 97,
		BDG_EXP_LOK_IMP_OUTPOST = 98,
		BDG_EXP_LOK_KIMOGILA_SKELETON = 99,
		BDG_EXP_10_BADGES = 100,
		BDG_EXP_20_BADGES = 101,
		BDG_EXP_30_BADGES = 102,
		BDG_EXP_40_BADGES = 103,
		BDG_EXP_45_BADGES = 104,
		BDG_THM_PARK_JABBA_BADGE = 105,
		BDG_THM_PARK_IMPERIAL_BADGE = 106,
		BDG_THM_PARK_REBEL_BADGE = 107,
		BDG_THM_PARK_NYM_BADGE = 108,
		EVENT_COA3_REBEL = 109,
		EVENT_COA3_IMPERIAL = 110,
		BDG_LIBRARY_TRIVIA = 111,
		BDG_CORVETTE_IMP_DESTROY = 112,
		BDG_CORVETTE_IMP_RESCUE = 113,
		BDG_CORVETTE_IMP_ASSASSIN = 114,
		BDG_CORVETTE_NEUTRAL_DESTROY = 115,
		BDG_CORVETTE_NEUTRAL_RESCUE = 116,
		BDG_CORVETTE_NEUTRAL_ASSASSIN = 117,
		BDG_CORVETTE_REB_DESTROY = 118,
		BDG_CORVETTE_REB_RESCUE = 119,
		BDG_CORVETTE_REB_ASSASSIN = 120,
		BDG_RACING_AGRILAT_SWAMP = 121,
		BDG_RACING_KEREN_CITY = 122,
		BDG_RACING_MOS_ESPA = 123,
		BDG_ACCOLADE_LIVE_EVENT = 124,
		BDG_RACING_LOK_MARATHON = 125,
		BDG_RACING_NARMLE_MEMORIAL = 126,
		BDG_RACING_NASHAL_RIVER = 127
	};

	//Fifth Bitmask
	enum {
		DESTROY_DEATHSTAR = 128,
		CRAFTING_SHIPWRIGHT = 129,
		PILOT_REBEL_NAVY_NABOO = 130,
		PILOT_REBEL_NAVY_CORELLIA = 131,
		PILOT_REBEL_NAVY_TATOOINE = 132,
		PILOT_IMPERIAL_NAVY_NABOO = 133,
		PILOT_IMPERIAL_NAVY_CORELLIA = 134,
		PILOT_IMPERIAL_NAVY_TATOOINE = 135,
		PILOT_NEUTRAL_NABOO = 136,
		PILOT_CORELLIA = 137,
		PILOT_TATOOINE = 138,
		BDG_ACCOLATE_HOME_SHOW = 139
	};

	//Types
	enum {
		MISC,
		QUEST,
		EXPLORATION,
		PROFESSION,
		EVENT,
		DUNGION 
	};

public:
		static String getName(uint8 badgeID) {
			return names[badgeID];
		}

		static uint8 getType(uint8 badgeID) {
			return types[badgeID];
		}

		static int getID(const String& name) {
			for (int i = 0; i < 140; i++) {
				if (name.compareTo(names[i]) == 0)
					return i;
			}

			return -1;
		}

		static bool exists(uint8 badgeID) {
			return badgeID < 140;
		}
};

#endif /*BADGE_H_*/
