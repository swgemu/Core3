--Copyright (C) 2008 <SWGEmu>


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
advancedUbeseArmorSegment = Object:new {

   objectName = "Advanced Ubese Armor Segment", -- name of the lua Object
   stfName = "armor_segment_ubese_advanced", 
   objectCRC = 83159329, 
   groupName = "craftArmorPersonalGroupE", 

   craftingToolTab = 2, 
   complexity = 20, 
   size = 6, 

   xpType = "crafting_clothing_armor", 
   xp = 100, 

   assemblySkill = "armor_assembly", 
   experimentingSkill = "armor_experimentation", 

   ingredientTemplateNames = "craft_armor_ingredients_n, craft_armor_ingredients_n, craft_armor_ingredients_n, craft_armor_ingredients_n, craft_armor_ingredients_n",
   ingredientTitleNames = "segment_layer_assembly_plate, armor_layer_weld_tabs, segment_mounting_tabs, defensive_layer, segment_enhancement",
   ingredientSlotType = "0, 0, 0, 1, 1",
   --resourceTypes = "iron_axidite, steel_neutronium, fiberplast, object/tangible/component/armor/shared_armor_layer.iff, object/tangible/component/armor/shared_base_armor_segment_enhancement.iff",
   resourceTypes = "metal, metal, metal, object/tangible/component/armor/shared_armor_layer.iff, object/tangible/component/armor/shared_base_armor_segment_enhancement.iff",
   resourceQuantities = "25, 15, 10, 1, 1",
   combineTypes = "1, 1, 1, 3, 3",
   contribution = "100, 100, 100, 100, 100",


  numberExperimentalProperties = "1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2",
   experimentalProperties = "XX, XX, XX, OQ, SR, OQ, UT, OQ, MA, OQ, MA, OQ, MA, XX, XX, OQ, SR",
   experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalGroupTitles = "exp_resistance, exp_durability, exp_quality",
   experimentalSubGroupCount = "1, 4, 1",
   experimentalSubGroupTitles = "kineticeffectiveness, armorIntegrity, armor_action_encumbrance, armor_health_encumbrance, armor_mind_encumbrance, base_effectiveness",

   tanoAttributes = "objecttype=262145:objectcrc=1032868484:objecttemp=armor_segment_ubese_advanced:templatetype=craft_clothing_ingredients_n:",
   customizationOptions = "",
   customizationDefaults = "",
   
   attributesToSet = "base_effectiveness, armorIntegrity, armor_action_encumbrance, armor_health_encumbrance, armor_mind_encumbrance,  kineticeffectiveness",
   attributeExperimentalProperties = "exp_quality, exp_durability, exp_durability, exp_durability, exp_durability, exp_resistance",
   attributePrecision = "10, 0, 0, 0, 0, 10",
   attributesMinMax = "1, 20, 1, 1000, 9, 1, 11, 1, 9, 1, 1, 30"
}

DraftSchematics:addDraftSchematic(advancedUbeseArmorSegment, 83159329)--- Add to global DraftSchematics table
