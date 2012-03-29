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

#ifndef WEARABLESKILLMODS_H_
#define WEARABLESKILLMODS_H_

#include "engine/engine.h"

/*
 * WearableSkillMods is a class that holds the methods and members to determine what skill
 * mods that wearables can have
 */

class WearableSkillMods : public Object {
public:
	/*
	 * Constructor
	 */
	WearableSkillMods() {

	}

	static String getRandomAttachmentMod(int type) {
		// Needs to have "cat_skill_mod_bonus.@stat_n:" before the stat name when sent to the client
		// Type is 1 = Clothing, 2 = Armor
		String randomskill = "";
		int randommod = System::random(94) + 1;

		switch (randommod) {
		case 1:
			randomskill = "weapon_repair";
			break;
		case 2:
			randomskill = "armor_repair";
			break;
		case 3:
			randomskill = "clothing_repair";
			break;
		case 4:
			randomskill = "droid_customization";
			break;
		case 5:
			randomskill = "droid_complexity";
			break;
		case 6:
			randomskill = "structure_complexity";
			break;
		case 7:
			randomskill = "surveying";
			break;
		case 8:
			randomskill = "healing_injury_treatment";
			break;
		case 9:
			randomskill = "healing_injury_speed";
			break;
		case 10:
			randomskill = "healing_wound_treatment";
			break;
		case 11:
			randomskill = "healing_wound_speed";
			break;
		case 12:
			randomskill = "medical_foraging";
			break;
		case 13:
			randomskill = "healing_ability";
			break;
		case 14:
			randomskill = "healing_range";
			break;
		case 15:
			randomskill = "healing_range_speed";
			break;
		case 16:
			randomskill = "combat_healing_ability";
			break;
		case 17:
			randomskill = "slope_move";
			break;
		case 18:
			randomskill = "camouflage";
			break;
		case 19:
			randomskill = "foraging";
			break;
		case 20:
			randomskill = "rescue";
			break;
		case 21:
			randomskill = "group_slope_move";
			break;
		case 22:
			randomskill = "steadyaim";
			break;
		case 23:
			randomskill = "volley";
			break;
		case 24:
			randomskill = "healing_range";
			break;
		case 25:
			randomskill = "keep_creature";
			break;
		case 26:
			randomskill = "stored_pets";
			break;
		case 27:
			randomskill = "tame_bonus";
			break;
		case 28:
			randomskill = "dodge";
			break;
		case 29:
			randomskill = "counterattack";
			break;
		case 30:
			randomskill = "block";
			break;
		case 31:
			randomskill = "resistance_bleeding";
			break;
		case 32:
			randomskill = "combat_bleeding_defense";
			break;
		case 33:
			randomskill = "resistance_poison";
			break;
		case 34:
			randomskill = "resistance_disease";
			break;
		case 35:
			randomskill = "resistance_fire";
			break;
		case 36:
			randomskill = "melee_defense";
			break;
		case 37:
			randomskill = "ranged_defense";
			break;
		case 38:
			randomskill = "dizzy_defense";
			break;
		case 39:
			randomskill = "blind_defense";
			break;
		case 40:
			randomskill = "knockdown_defense";
			break;
		case 41:
			randomskill = "posture_change_up_defense";
			break;
		case 42:
			randomskill = "posture_change_down_defense";
			break;
		case 43:
			randomskill = "intimidate_defense";
			break;
		case 44:
			randomskill = "stun_defense";
			break;
		case 45:
			randomskill = "unarmed_speed";
			break;
		case 46:
			randomskill = "unarmed_accuracy";
			break;
		case 47:
			randomskill = "onehandmelee_speed";
			break;
		case 48:
			randomskill = "onehandmelee_accuracy";
			break;
		case 49:
			randomskill = "twohandmelee_speed";
			break;
		case 50:
			randomskill = "twohandmelee_accuracy";
			break;
		case 51:
			randomskill = "polearm_speed";
			break;
		case 52:
			randomskill = "polearm_accuracy";
			break;
		case 53:
			randomskill = "warcry";
			break;
		case 54:
			randomskill = "berserk";
			break;
		case 55:
			randomskill = "intimidate";
			break;
		case 56:
			randomskill = "unarmed_damage";
			break;
		case 57:
			randomskill = "onehandmelee_damage";
			break;
		case 58:
			randomskill = "twohandmelee_damage";
			break;
		case 60:
			randomskill = "aim";
			break;
		case 61:
			randomskill = "alert";
			break;
		case 62:
			randomskill = "stun_defense";
			break;
		case 63:
			randomskill = "carbine_speed";
			break;
		case 64:
			randomskill = "carbine_accuracy";
			break;
		case 65:
			randomskill = "carbine_hit_while_moving";
			break;
		case 66:
			randomskill = "carbine_aim";
			break;
		case 67:
			randomskill = "pistol_speed";
			break;
		case 68:
			randomskill = "pistol_accuracy";
			break;
		case 69:
			randomskill = "pistol_hit_while_moving";
			break;
		case 70:
			randomskill = "pistol_standing";
			break;
		case 71:
			randomskill = "pistol_aim";
			break;
		case 72:
			randomskill = "rifle_speed";
			break;
		case 73:
			randomskill = "rifle_accuracy";
			break;
		case 74:
			randomskill = "rifle_hit_while_moving";
			break;
		case 75:
			randomskill = "rifle_aim";
			break;
		case 76:
			randomskill = "cover";
			break;
		case 77:
			randomskill = "take_cover";
			break;
		case 78:
			randomskill = "rifle_prone";
			break;
		case 79:
			randomskill = "thrown_accuracy";
			break;
		case 80:
			randomskill = "thrown_speed";
			break;
		case 81:
			randomskill = "heavyweapon_speed";
			break;
		case 82:
			randomskill = "heavyweapon_accuracy";
			break;
		case 83:
			randomskill = "droid_tracks"; //Tracking Droids
			break;
		case 84:
			randomskill = "droid_track_chance"; //Tracking Droid Effectiveness
			break;
		case 85:
			randomskill = "droid_find_speed"; //Droid Speed
			break;
		case 86:
			randomskill = "droid_find_chance"; //Droid Precision
			break;
		case 87:
			randomskill = "healing_music_wound";
			break;
		case 88:
			randomskill = "healing_dance_wound";
			break;
		case 89:
			randomskill = "healing_music_shock";
			break;
		case 90:
			randomskill = "healing_dance_shock";
			break;
		case 91:
			randomskill = "healing_music_mind";
			break;
		case 92:
			randomskill = "healing_dance_mind";
			break;
		case 93:
			randomskill = "instrument_assembly";
			break;
		case 59:
		case 94:
			// Wohooo!  Crafting Mods!
			if (type == 1) {
				int randomcraftingmod = System::random(21) + 1;

				switch (randomcraftingmod) {
				case 1:
					randomskill = "weapon_experimentation";
					break;
				case 2:
					randomskill = "weapon_assembly";
					break;
				case 3:
					randomskill = "armor_experimentation";
					break;
				case 4:
					randomskill = "armor_assembly";
					break;
				case 5:
					randomskill = "food_experimentation";
					break;
				case 6:
					randomskill = "food_assembly";
					break;
				case 7:
					randomskill = "medicine_experimentation";
					break;
				case 8:
					randomskill = "medicine_assembly";
					break;
				case 9:
					randomskill = "combat_medicine_experimentation";
					break;
				case 10:
					randomskill = "combat_medicine_assembly";
					break;
				case 11:
					randomskill = "droid_experimentation";
					break;
				case 12:
					randomskill = "droid_assembly";
					break;
				case 13:
					randomskill = "clothing_experimentation";
					break;
				case 14:
					randomskill = "clothing_assembly";
					break;
				case 15:
					randomskill = "structure_experimentation";
					break;
				case 16:
					randomskill = "structure_assembly";
					break;
				case 17:
					randomskill = "general_experimentation";
					break;
				case 18:
					randomskill = "general_assembly";
					break;
				case 19:
					randomskill = "grenade_experimentation";
					break;
				case 20:
					randomskill = "grenade_assembly";
					break;
				case 21:
					randomskill = "jedi_saber_assembly";
					break;
				case 22:
					randomskill = "jedi_saber_experimentation";
					break;
				}
			} else {
				randomskill = "armor_repair";
			}
			break;
		case 95:
			// Jedi mods didn't exist, commenting out to keep for reference.
			if (type == 1) {
				/*
				int randomjedimod = System::random(10) + 1;

				switch (randomjedimod) {
				case 1:
					randomskill = "forcelightning_accuracy";
					break;
				case 2:
					randomskill = "forcethrow_accuracy";
					break;
				case 3:
					randomskill = "jedi_force_power_max";
					break;
				case 4:
					randomskill = "jedi_force_power_regen";
					break;
				case 5:
					randomskill = "onehandlightsaber_accuracy";
					break;
				case 6:
					randomskill = "onehandlightsaber_speed";
					break;
				case 7:
					randomskill = "polearmlightsaber_accuracy";
					break;
				case 8:
					randomskill = "polearmlightsaber_speed";
					break;
				case 9:
					randomskill = "saber_block";
					break;
				case 10:
					randomskill = "twohandlightsaber_accuracy";
					break;
				case 11:
					randomskill = "twohandlightsaber_speed";*/
					randomskill = "instrument_assembly";
					break;
				}
			} else {
				randomskill = "instrument_assembly";
			}
			break;
		}
		return randomskill;
	}

};

#endif /*WEARABLESKILLMODS_H_*/
