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


object_draft_schematic_droid_droid_power = object_draft_schematic_droid_shared_droid_power:new {

   templateType = DRAFTSCHEMATIC,

   customObjectName = "Deed for: Power Droid",

   craftingToolTab = 32, -- (See DraftSchematicObjectTemplate.h)
   complexity = 18, 
   size = 3, 

   xpType = "crafting_droid_general", 
   xp = 300, 

   assemblySkill = "droid_assembly", 
   experimentingSkill = "droid_experimentation", 
   customizationSkill = "droid_customization", 

   customizationOptions = {},
   customizationStringNames = {},
   customizationDefaults = {},

   ingredientTemplateNames = {"craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n"},
   ingredientTitleNames = {"primary_frame", "body_shell", "thermal_shielding", "generator_shell_hardening", "droid_brain", "engine_unit", "power_module", "sensor_suite", "general_droid_module"},
   ingredientSlotType = {0, 0, 0, 0, 1, 1, 1, 1, 3},
   resourceTypes = {"metal", "fiberplast", "ore", "steel", "object/tangible/component/droid/shared_droid_brain.iff", "object/tangible/component/droid/shared_droid_motive_system.iff", "object/tangible/component/structure/shared_power_core_unit.iff", "object/tangible/component/droid/shared_sensor_package_droid.iff", "object/tangible/component/droid/shared_droid_service_module_base.iff"},
   resourceQuantities = {40, 60, 20, 30, 1, 1, 1, 1, 1},
   contribution = {100, 100, 100, 100, 100, 100, 100, 100, 100},


   targetTemplate = "object/tangible/deed/pet_deed/deed_power_basic.iff",

   additionalTemplates = {
             }

}
ObjectTemplates:addTemplate(object_draft_schematic_droid_droid_power, "object/draft_schematic/droid/droid_power.iff")
