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


object_draft_schematic_weapon_heavy_rocket_launcher = object_draft_schematic_weapon_shared_heavy_rocket_launcher:new {

   templateType = DRAFTSCHEMATIC,

   customObjectName = "Rocket Launcher",

   craftingToolTab = 1, -- (See DraftSchemticImplementation.h)
   complexity = 50, 
   size = 4, 

   xpType = "crafting_weapons_general", 
   xp = 770, 

   assemblySkill = "weapon_assembly", 
   experimentingSkill = "weapon_experimentation", 
   customizationSkill = "weapon_customization", 

   customizationOptions = {},
   customizationStringNames = {},
   customizationDefaults = {},

   ingredientTemplateNames = {"craft_weapon_ingredients_n", "craft_weapon_ingredients_n", "craft_weapon_ingredients_n", "craft_munition_ingredients_n", "craft_munition_ingredients_n", "craft_munition_ingredients_n", "craft_munition_ingredients_n", "craft_munition_ingredients_n"},
   ingredientTitleNames = {"frame_assembly", "receiver_assembly", "grip_assembly", "ignition_pulse_generator", "launch_tubes", "shell_handling_unit", "warheads", "target_tracker"},
   ingredientSlotType = {0, 0, 0, 1, 0, 1, 1, 1},
   resourceTypes = {"iron", "metal", "metal", "object/tangible/component/weapon/shared_blaster_power_handler.iff", "steel", "object/tangible/component/weapon/shared_projectile_feed_mechanism.iff", "object/weapon/ranged/grenade/shared_grenade_proton.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"},
   resourceQuantities = {150, 40, 25, 4, 170, 8, 5, 2},
   contribution = {100, 100, 100, 100, 100, 100, 100, 100},


   targetTemplate = "object/weapon/ranged/heavy/heavy_rocket_launcher.iff",

   additionalTemplates = {
             }

}
ObjectTemplates:addTemplate(object_draft_schematic_weapon_heavy_rocket_launcher, "object/draft_schematic/weapon/heavy_rocket_launcher.iff")
