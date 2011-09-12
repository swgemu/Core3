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


object_draft_schematic_droid_component_chassis_droid_r2 = object_draft_schematic_droid_component_shared_chassis_droid_r2:new {

   templateType = DRAFTSCHEMATIC,

   customObjectName = "R2 ADV Droid Chassis",

   craftingToolTab = 32, -- (See DraftSchemticImplementation.h)
   complexity = 25, 
   size = 8, 

   xpType = "crafting_droid_general", 
   xp = 210, 

   assemblySkill = "droid_assembly", 
   experimentingSkill = "droid_experimentation", 
   customizationSkill = "droid_customization", 

   customizationOptions = {},
   customizationStringNames = {},
   customizationDefaults = {},

   ingredientTemplateNames = {"craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n", "craft_droid_ingredients_n"},
   ingredientTitleNames = {"primary_body_shell", "secondary_body_structure", "frame", "intellex_iv_computer", "manipulator_arm", "motivator", "sensor_suite"},
   ingredientSlotType = {0, 0, 2, 2, 2, 2, 2},
   resourceTypes = {"chemical", "chemical", "object/tangible/component/droid/shared_advanced_droid_frame.iff", "object/tangible/component/droid/shared_droid_brain_advanced.iff", "object/tangible/component/droid/shared_manipulator_arm_package_set.iff", "object/tangible/component/droid/shared_droid_motive_system_advanced.iff", "object/tangible/component/droid/shared_sensor_package_droid.iff"},
   resourceQuantities = {120, 90, 1, 1, 1, 1, 1},
   combineTypes = {0, 0, 1, 1, 1, 1, 1},
   contribution = {100, 100, 100, 100, 100, 100, 100},


   targetTemplate = "object/tangible/component/droid/r2_droid_chassis.iff",

   additionalTemplates = {
              "object/tangible/component/droid/shared_r2_droid_chassis.iff",
             }

}
ObjectTemplates:addTemplate(object_draft_schematic_droid_component_chassis_droid_r2, "object/draft_schematic/droid/component/chassis_droid_r2.iff")
