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
		static const uint8 COUNT_5 = 0;
		static const uint8 COUNT_10 = 1;
		static const uint8 COUNT_25 = 2;
		static const uint8 COUNT_50 = 3;
		static const uint8 COUNT_75 = 4;
		static const uint8 COUNT_100 = 5;
		static const uint8 COUNT_125 = 6;
		static const uint8 POI_RABIDBEAST = 7;
		static const uint8 POI_PRISONBREAK = 8;
		static const uint8 POI_TWOLIARS = 9;
		static const uint8 POI_FACTORYLIBERATION = 10;
		static const uint8 POI_HEROMARK = 11;
		static const uint8 EXP_TAT_BENS_HUT = 12;
		static const uint8 EXP_TAT_TUSKEN_POOL = 13;
		static const uint8 EXP_TAT_KRAYT_SKELETON = 14;
		static const uint8 EXP_TAT_ESCAPE_POD = 15;
		static const uint8 EXP_TAT_SARLACC_PIT = 16;
		static const uint8 EXP_TAT_LARS_HOMESTEAD = 17;
		static const uint8 EXP_TAT_KRAYT_GRAVEYARD = 18;
		static const uint8 EXP_NAB_GUNGAN_SACRED_PLACE = 19;
		static const uint8 EXP_COR_AGRILAT_SWAMP = 20;
		static const uint8 EXP_YAV_TEMPLE_WOOLAMANDER = 21;
		static const uint8 EXP_YAV_TEMPLE_BLUELEAF = 22;
		static const uint8 EXP_YAV_TEMPLE_EXAR_KUN = 23;
		static const uint8 EXP_LOK_VOLCANO = 24;
		static const uint8 EXP_DAT_TARPIT = 25;
		static const uint8 EXP_DAT_SARLACC = 26;
		static const uint8 EXP_DAT_ESCAPE_POD = 27;
		static const uint8 EXP_DAT_MISTY_FALLS_1 = 28;
		static const uint8 EXP_DAT_MISTY_FALLS_2 = 29;
		static const uint8 EXP_DAN_JEDI_TEMPLE = 30;
		static const uint8 EXP_DAN_REBEL_BASE = 31;

		//Second Bitmask
		static const uint8 EVENT_PROJECT_DEAD_EYE_1 = 32;
		static const uint8 ACC_GOOD_SAMARITAN = 33;
		static const uint8 ACC_FASCINATING_BACKGROUND = 34;
		static const uint8 ACC_BRAVE_SOLDIER = 35;
		static const uint8 ACC_INTERESTING_PERSONAGE = 36;
		static const uint8 ACC_PROFESSIONAL_DEMEANOR = 37;
		static const uint8 WARREN_COMPASSION = 38;
		static const uint8 WARREN_HERO = 39;
		static const uint8 EVENT_COA2_REBEL = 40;
		static const uint8 EVENT_COA2_IMPERIAL = 41;
		static const uint8 COMBAT_1HSWORD_MASTER = 42;
		static const uint8 COMBAT_2HSWORD_MASTER = 43;
		static const uint8 COMBAT_BOUNTYHUNTER_MASTER = 44;
		static const uint8 COMBAT_BRAWLER_MASTER = 45;
		static const uint8 COMBAT_CARBINE_MASTER = 46;
		static const uint8 COMBAT_COMMANDO_MASTER = 47;
		static const uint8 COMBAT_MARKSMAN_MASTER = 48;
		static const uint8 COMBAT_PISTOL_MASTER = 49;
		static const uint8 COMBAT_POLEARM_MASTER = 50;
		static const uint8 COMBAT_RIFLEMAN_MASTER = 51;
		static const uint8 COMBAT_SMUGGLER_MASTER = 52;
		static const uint8 COMBAT_UNARMED_MASTER = 53;
		static const uint8 CRAFTING_ARCHITECT_MASTER = 54;
		static const uint8 CRAFTING_ARMORSMITH_MASTER = 55;
		static const uint8 CRAFTING_ARTISAN_MASTER = 56;
		static const uint8 CRAFTING_CHEF_MASTER = 57;
		static const uint8 CRAFTING_DROIDENGINEER_MASTER = 58;
		static const uint8 CRAFTING_MERCHANT_MASTER = 59;
		static const uint8 CRAFTING_TAILOR_MASTER = 60;
		static const uint8 CRAFTING_WEAPONSMITH_MASTER = 61;
		static const uint8 OUTDOORS_BIOENGINEER_MASTER = 62;
		static const uint8 OUTDOORS_CREATUREHANDLER_MASTER = 63;

		//Third Bitmask
		static const uint8 OUTDOORS_RANGER_MASTER = 64;
		static const uint8 OUTDOORS_SCOUT_MASTER = 65;
		static const uint8 OUTDOORS_SQUADLEADER_MASTER = 66;
		static const uint8 SCIENCE_COMBATMEDIC_MASTER = 67;
		static const uint8 SCIENCE_DOCTOR_MASTER = 68;
		static const uint8 SCIENCE_MEDIC_MASTER = 69;
		static const uint8 SOCIAL_DANCER_MASTER = 70;
		static const uint8 SOCIAL_ENTERTAINER_MASTER = 71;
		static const uint8 SOCIAL_IMAGEDESIGNER_MASTER = 72;
		static const uint8 SOCIAL_MUSICIAN_MASTER = 73;
		static const uint8 SOCIAL_POLITICIAN_MASTER = 74;
		static const uint8 BDG_EXP_NAB_THEED_FALLS_BOTTOM = 75;
		static const uint8 BDG_EXP_NAB_DEEJA_FALLS_TOP = 76;
		static const uint8 BDG_EXP_NAB_AMIDALAS_SANDY_BEACH = 77;
		static const uint8 BDG_EXP_COR_REBEL_HIDEOUT = 78;
		static const uint8 BDG_EXP_COR_ROGUE_CORSEC_BASE = 79;
		static const uint8 BDG_EXP_COR_TYRENA_THEATER = 80;
		static const uint8 BDG_EXP_COR_BELA_VISTAL_FOUNTAIN = 81;
		static const uint8 BDG_EXP_DAT_CRASHED_SHIP = 82;
		static const uint8 BDG_EXP_DAT_IMP_PRISON = 83;
		static const uint8 BDG_EXP_DAN_DANTARI_VILLAGE1 = 84;
		static const uint8 BDG_EXP_DAN_DANTARI_VILLAGE2 = 85;
		static const uint8 BDG_EXP_END_EWOK_TREE_VILLAGE = 86;
		static const uint8 BDG_EXP_END_EWOK_LAKE_VILLAGE = 87;
		static const uint8 BDG_EXP_END_DULOK_VILLAGE = 88;
		static const uint8 BDG_EXP_END_IMP_OUTPOST = 89;
		static const uint8 BDG_EXP_TAL_CREATURE_VILLAGE = 90;
		static const uint8 BDG_EXP_TAL_IMP_BASE = 91;
		static const uint8 BDG_EXP_TAL_IMP_VS_REB_BATTLE = 92;
		static const uint8 BDG_EXP_TAL_AQUALISH_CAVE = 93;
		static const uint8 BDG_EXP_ROR_KOBALA_SPICE_MINE = 94;
		static const uint8 BDG_EXP_ROR_REBEL_OUTPOST = 95;

		//Fourth Bitmask
		static const uint8 BDG_EXP_ROR_IMP_CAMP = 96;
		static const uint8 BDG_EXP_ROR_IMP_HYPERDRIVE_FAC = 97;
		static const uint8 BDG_EXP_LOK_IMP_OUTPOST = 98;
		static const uint8 BDG_EXP_LOK_KIMOGILA_SKELETON = 99;
		static const uint8 BDG_EXP_10_BADGES = 100;
		static const uint8 BDG_EXP_20_BADGES = 101;
		static const uint8 BDG_EXP_30_BADGES = 102;
		static const uint8 BDG_EXP_40_BADGES = 103;
		static const uint8 BDG_EXP_45_BADGES = 104;
		static const uint8 BDG_THM_PARK_JABBA_BADGE = 105;
		static const uint8 BDG_THM_PARK_IMPERIAL_BADGE = 106;
		static const uint8 BDG_THM_PARK_REBEL_BADGE = 107;
		static const uint8 BDG_THM_PARK_NYM_BADGE = 108;
		static const uint8 EVENT_COA3_REBEL = 109;
		static const uint8 EVENT_COA3_IMPERIAL = 110;
		static const uint8 BDG_LIBRARY_TRIVIA = 111;
		static const uint8 BDG_CORVETTE_IMP_DESTROY = 112;
		static const uint8 BDG_CORVETTE_IMP_RESCUE = 113;
		static const uint8 BDG_CORVETTE_IMP_ASSASSIN = 114;
		static const uint8 BDG_CORVETTE_NEUTRAL_DESTROY = 115;
		static const uint8 BDG_CORVETTE_NEUTRAL_RESCUE = 116;
		static const uint8 BDG_CORVETTE_NEUTRAL_ASSASSIN = 117;
		static const uint8 BDG_CORVETTE_REB_DESTROY = 118;
		static const uint8 BDG_CORVETTE_REB_RESCUE = 119;
		static const uint8 BDG_CORVETTE_REB_ASSASSIN = 120;
		static const uint8 BDG_RACING_AGRILAT_SWAMP = 121;
		static const uint8 BDG_RACING_KEREN_CITY = 122;
		static const uint8 BDG_RACING_MOS_ESPA = 123;
		static const uint8 BDG_ACCOLADE_LIVE_EVENT = 124;
		static const uint8 BDG_RACING_LOK_MARATHON = 125;
		static const uint8 BDG_RACING_NARMLE_MEMORIAL = 126;
		static const uint8 BDG_RACING_NASHAL_RIVER = 127;

		//Fifth Bitmask
		static const uint8 DESTROY_DEATHSTAR = 128;
		static const uint8 CRAFTING_SHIPWRIGHT = 129;
		static const uint8 PILOT_REBEL_NAVY_NABOO = 130;
		static const uint8 PILOT_REBEL_NAVY_CORELLIA = 131;
		static const uint8 PILOT_REBEL_NAVY_TATOOINE = 132;
		static const uint8 PILOT_IMPERIAL_NAVY_NABOO = 133;
		static const uint8 PILOT_IMPERIAL_NAVY_CORELLIA = 134;
		static const uint8 PILOT_IMPERIAL_NAVY_TATOOINE = 135;
		static const uint8 PILOT_NEUTRAL_NABOO = 136;
		static const uint8 PILOT_CORELLIA = 137;
		static const uint8 PILOT_TATOOINE = 138;
		static const uint8 BDG_ACCOLATE_HOME_SHOW = 139;

		//Types
		static const uint8 MISC = 0;
		static const uint8 QUEST = 1;
		static const uint8 EXPLORATION = 2;
		static const uint8 PROFESSION = 3;
		static const uint8 EVENT = 4;
		static const uint8 DUNGION = 5;

public:
		static String getName(uint8 badgeID) {
			return names[badgeID];
		}

		static uint8 getType(uint8 badgeID) {
			return types[badgeID];
		}

		static int getID(String name) {
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
