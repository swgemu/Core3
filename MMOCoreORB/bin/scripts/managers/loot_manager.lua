--Copyright (C) 2007 <SWGEmu>
 
--This File is part of Core3.
 
--This program is free software; you can redistribute 
--it and/or modify it under the terms of the GNU Lesser 
--General Public License as published by the Free Software
--Foundation; either version 2 of the License, 
--or (at your option) any later version.
 
--This program is distributed in the hope that it will be useful, 
--but WITHOUT ANY WARRANTY; without even the implied warranty of 
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
--See the GNU Lesser General Public License for
--more details.
 
--You should have received a copy of the GNU Lesser General 
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
--Linking Engine3 statically or dynamically with other modules 
--is making a combined work based on Engine3. 
--Thus, the terms and conditions of the GNU Lesser General Public License 
--cover the whole combination.
 
--In addition, as a special exception, the copyright holders of Engine3 
--give you permission to combine Engine3 program with free software 
--programs or libraries that are released under the GNU LGPL and with 
--code included in the standard release of Core3 under the GNU LGPL 
--license (or modified versions of such code, with unchanged license). 
--You may copy and distribute such a system following the terms of the 
--GNU LGPL for Engine3 and the licenses of the other code concerned, 
--provided that you include the source code of that other code when 
--and as the GNU LGPL requires distribution of source code.
 
--Note that people who make modified versions of Engine3 are not obligated 
--to grant this special exception for their modified versions; 
--it is their choice whether to do so. The GNU Lesser General Public License 
--gives permission to release a modified version without this exception; 
--this exception also makes it possible to release a modified version 
--which carries forward this exception.

--Determines how often exceptional and legendary items can drop.
exceptionalChance = 0.001
legendaryChance = 0.0001

--Determines how much of an increase in the base stats will be applied to the object.
exceptionalModifier = 0.20
legendaryModifier = 0.40

lootableStatMods = {
	"aim",
	"alert",
	"armor_assembly",
	"armor_experimentation",
	"armor_repair",
	"berserk",
	"blind_defense",
	"block",
	"camouflage",
	"carbine_accuracy",
	"carbine_aim",
	"carbine_hit_while_moving",
	"carbine_speed",
	"clothing_assembly",
	"clothing_experimentation",
	"clothing_repair",
	"combat_bleeding_defense",
	"combat_healing_ability",
	"combat_medicine_assembly",
	"combat_medicine_experimentation",
	"counterattack",
	"cover",
	"dizzy_defense",
	"dodge",
	"droid_assembly",
	"droid_complexity",
	"droid_customization",
	"droid_experimentation",
	"droid_find_chance",
	"droid_find_speed",
	"droid_track_chance",
	"droid_tracks",
	"food_assembly",
	"food_experimentation",
	"foraging",
	"forcelightning_accuracy",
	"forcethrow_accuracy",
	"general_assembly",
	"general_experimentation",
	"grenade_assembly",
	"grenade_experimentation",
	"group_slope_move",
	"healing_ability",
	"healing_dance_mind",
	"healing_dance_shock",
	"healing_dance_wound",
	"healing_injury_speed",
	"healing_injury_treatment",
	"healing_music_mind",
	"healing_music_shock",
	"healing_music_wound",
	"healing_range",
	"healing_range",
	"healing_range_speed",
	"healing_wound_speed",
	"healing_wound_treatment",
	"heavyweapon_accuracy",
	"heavyweapon_speed",
	"instrument_assembly",
	"intimidate",
	"intimidate_defense",
	"jedi_force_power_max",
	"jedi_force_power_regen",
	"jedi_saber_assembly",
	"jedi_saber_experimentation",
	"keep_creature",
	"knockdown_defense",
	"medical_foraging",
	"medicine_assembly",
	"medicine_experimentation",
	"melee_defense",
	"onehandlightsaber_accuracy",
	"onehandlightsaber_speed",
	"onehandmelee_accuracy",
	"onehandmelee_damage",
	"onehandmelee_speed",
	"pistol_accuracy",
	"pistol_aim",
	"pistol_hit_while_moving",
	"pistol_speed",
	"pistol_standing",
	"polearm_accuracy",
	"polearm_speed",
	"polearmlightsaber_accuracy",
	"polearmlightsaber_speed",
	"posture_change_down_defense",
	"posture_change_up_defense",
	"ranged_defense",
	"rescue",
	"resistance_bleeding",
	"resistance_disease",
	"resistance_fire",
	"resistance_poison",
	"rifle_accuracy",
	"rifle_aim",
	"rifle_hit_while_moving",
	"rifle_prone",
	"rifle_speed",
	"saber_block",
	"slope_move",
	"steadyaim",
	"stored_pets",
	"structure_assembly",
	"structure_complexity",
	"structure_experimentation",
	"stun_defense",
	"stun_defense",
	"surveying",
	"take_cover",
	"tame_bonus",
	"thrown_accuracy",
	"thrown_speed",
	"twohandlightsaber_accuracy",
	"twohandlightsaber_speed",
	"twohandmelee_accuracy",
	"twohandmelee_damage",
	"twohandmelee_speed",
	"unarmed_accuracy",
	"unarmed_damage",
	"unarmed_speed",
	"volley",
	"warcry",
	"weapon_assembly",
	"weapon_experimentation",
	"weapon_repair"
}