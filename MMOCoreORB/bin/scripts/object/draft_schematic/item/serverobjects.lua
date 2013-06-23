--Copyright (C) 2010 <SWGEmu>


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



--Children folder includes
includeFile("draft_schematic/item/component/serverobjects.lua")
includeFile("draft_schematic/item/quest_item/serverobjects.lua")
includeFile("draft_schematic/item/theme_park/serverobjects.lua")

-- Server Objects
includeFile("draft_schematic/item/craftable_bug_habitat.lua")
includeFile("draft_schematic/item/item_agitator_motor.lua")
includeFile("draft_schematic/item/item_ballot_box_terminal.lua")
includeFile("draft_schematic/item/item_base_tool.lua")
includeFile("draft_schematic/item/item_battery_droid.lua")
includeFile("draft_schematic/item/item_chance_cube.lua")
includeFile("draft_schematic/item/item_clothing_station.lua")
includeFile("draft_schematic/item/item_clothing_tool.lua")
includeFile("draft_schematic/item/item_configurable_sided_dice.lua")
includeFile("draft_schematic/item/item_firework_eighteen.lua")
includeFile("draft_schematic/item/item_firework_eleven.lua")
includeFile("draft_schematic/item/item_firework_five.lua")
includeFile("draft_schematic/item/item_firework_four.lua")
includeFile("draft_schematic/item/item_firework_one.lua")
includeFile("draft_schematic/item/item_firework_show.lua")
includeFile("draft_schematic/item/item_firework_ten.lua")
includeFile("draft_schematic/item/item_firework_three.lua")
includeFile("draft_schematic/item/item_firework_two.lua")
includeFile("draft_schematic/item/item_fishing_pole.lua")
includeFile("draft_schematic/item/item_food_station.lua")
includeFile("draft_schematic/item/item_food_tool.lua")
includeFile("draft_schematic/item/item_generic_tool.lua")
includeFile("draft_schematic/item/item_hundred_sided_dice.lua")
includeFile("draft_schematic/item/item_jedi_tool.lua")
includeFile("draft_schematic/item/item_parrot_cage.lua")
includeFile("draft_schematic/item/item_powerup_weapon_melee_generic.lua")
includeFile("draft_schematic/item/item_powerup_weapon_melee_lightsaber.lua")
includeFile("draft_schematic/item/item_powerup_weapon_mine_explosive.lua")
includeFile("draft_schematic/item/item_powerup_weapon_ranged_five.lua")
includeFile("draft_schematic/item/item_powerup_weapon_ranged_four.lua")
includeFile("draft_schematic/item/item_powerup_weapon_ranged_one.lua")
includeFile("draft_schematic/item/item_powerup_weapon_ranged_six.lua")
includeFile("draft_schematic/item/item_powerup_weapon_ranged_three.lua")
includeFile("draft_schematic/item/item_powerup_weapon_ranged_two.lua")
includeFile("draft_schematic/item/item_powerup_weapon_thrown_explosive.lua")
includeFile("draft_schematic/item/item_powerup_weapon_thrown_wiring.lua")
includeFile("draft_schematic/item/item_public_clothing_station.lua")
includeFile("draft_schematic/item/item_public_food_station.lua")
includeFile("draft_schematic/item/item_public_structure_station.lua")
includeFile("draft_schematic/item/item_public_weapon_station.lua")
includeFile("draft_schematic/item/item_recycler_chemical.lua")
includeFile("draft_schematic/item/item_recycler_creature.lua")
includeFile("draft_schematic/item/item_recycler_flora.lua")
includeFile("draft_schematic/item/item_recycler_metal.lua")
includeFile("draft_schematic/item/item_recycler_ore.lua")
includeFile("draft_schematic/item/item_repairkit_armor.lua")
includeFile("draft_schematic/item/item_repairkit_clothing.lua")
includeFile("draft_schematic/item/item_repairkit_droid.lua")
includeFile("draft_schematic/item/item_repairkit_structure.lua")
includeFile("draft_schematic/item/item_repairkit_weapon.lua")
includeFile("draft_schematic/item/item_shellfish_harvester.lua")
includeFile("draft_schematic/item/item_six_sided_dice.lua")
includeFile("draft_schematic/item/item_space_station.lua")
includeFile("draft_schematic/item/item_space_tool.lua")
includeFile("draft_schematic/item/item_structure_station.lua")
includeFile("draft_schematic/item/item_structure_tool.lua")
includeFile("draft_schematic/item/item_survey_tool_flora.lua")
includeFile("draft_schematic/item/item_survey_tool_gas.lua")
includeFile("draft_schematic/item/item_survey_tool_liquid.lua")
includeFile("draft_schematic/item/item_survey_tool_mineral.lua")
includeFile("draft_schematic/item/item_survey_tool_moisture.lua")
includeFile("draft_schematic/item/item_survey_tool_solar.lua")
includeFile("draft_schematic/item/item_survey_tool_wind.lua")
includeFile("draft_schematic/item/item_ten_sided_dice.lua")
includeFile("draft_schematic/item/item_tumble_blender.lua")
includeFile("draft_schematic/item/item_twelve_sided_dice.lua")
includeFile("draft_schematic/item/item_twenty_sided_dice.lua")
includeFile("draft_schematic/item/item_weapon_station.lua")
includeFile("draft_schematic/item/item_weapon_tool.lua")
