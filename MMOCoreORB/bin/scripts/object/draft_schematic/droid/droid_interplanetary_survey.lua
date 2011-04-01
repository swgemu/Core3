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


object_draft_schematic_droid_droid_interplanetary_survey = object_draft_schematic_droid_shared_droid_interplanetary_survey:new {

   templateType = DRAFTSCHEMATIC,

   customObjectName = "Interplanetary Survey Droid",

   groupName = "craftdroidGroupF", -- Group schematic is awarded in (See skills table)

   craftingToolTab = 32, -- (See DraftSchemticImplementation.h)
   complexity = 25, 
   size = 1, 

   xpType = "crafting_droid_general", 
   xp = 380, 

   assemblySkill = "droid_assembly", 
   experimentingSkill = "droid_experimentation", 
   customizationSkill = "droid_customization", 

   customizationOptions = {},
   customizationStringNames = {},
   customizationDefaults = {},

   ingredientTemplateNames = {"craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n"},
   ingredientTitleNames = {"primary_frame", "body_shell", "shielding_and_insulation", "communication_array", "transportation_module", "survey_control_circuit", "survey_scanning_storage_circuit", "command_interpreter", "navigation_control_circuit"},
   ingredientSlotType = {0, 0, 0, 0, 0, 2, 2, 2, 2},
   resourceTypes = {"steel_carbonite", "chemical", "chemical", "crystalline_vertex", "radioactive_known", "object/tangible/component/item/shared_electronics_gp_module.iff", "object/tangible/component/item/shared_electronics_memory_module.iff", "object/tangible/component/item/shared_electronics_gp_module.iff", "object/tangible/component/item/shared_electronics_gp_module.iff"},
   resourceQuantities = {40, 20, 25, 30, 35, 1, 1, 1, 1},
   combineTypes = {0, 0, 0, 0, 0, 1, 1, 1, 1},
   contribution = {100, 100, 100, 100, 100, 100, 100, 100, 100},

   templates { = 
              3351452767, -- Script: 'object/tangible/component/droid/droid_interplanetary_survey.iff'
             }

}
ObjectTemplates:addTemplate(object_draft_schematic_droid_droid_interplanetary_survey, "object/draft_schematic/droid/droid_interplanetary_survey.iff")
