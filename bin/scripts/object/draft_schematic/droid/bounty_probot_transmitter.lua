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


object_draft_schematic_droid_bounty_probot_transmitter = object_draft_schematic_droid_shared_bounty_probot_transmitter:new {

   templateType = DRAFTSCHEMATIC,

   customObjectName = "Arakyd Probe Droid",

   groupName = "craftdroidGroupD", -- Group schematic is awarded in (See skills table)

   craftingToolTab = 32, -- (See DraftSchemticImplementation.h)
   complexity = 25, 
   size = 1, 

   xpType = "crafting_droid_general", 
   xp = 340, 

   assemblySkill = "droid_assembly", 
   experimentingSkill = "droid_experimentation", 
   customizationSkill = "droid_customization", 

   customizationOptions = {},
   customizationStringNames = {},
   customizationDefaults = {},

   ingredientTemplateNames = {"craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n"},
   ingredientTitleNames = {"primary_frame", "body_shell", "shielding_and_insulation", "advanced_search_planning_circuit", "search_parameter_storage_circuit", "command_interpreter", "autonomous_searcher_logic_unit"},
   ingredientSlotType = {0, 0, 0, 1, 1, 1, 1},
   resourceTypes = {"steel", "chemical", "ore_extrusive", "object/tangible/component/item/shared_electronics_gp_module.iff", "object/tangible/component/item/shared_electronics_memory_module.iff", "object/tangible/component/item/shared_electronics_gp_module.iff", "object/tangible/component/item/shared_electronics_gp_module.iff"},
   resourceQuantities = {30, 20, 25, 1, 1, 1, 1},
   combineTypes = {0, 0, 0, 1, 1, 1, 1},
   contribution = {100, 100, 100, 100, 100, 100, 100},

   templates = {
              97250743, -- Script: 'object/tangible/mission/mission_bounty_droid_probot.iff'
             }

}
ObjectTemplates:addTemplate(object_draft_schematic_droid_bounty_probot_transmitter, "object/draft_schematic/droid/bounty_probot_transmitter.iff")
