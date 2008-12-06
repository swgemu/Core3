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
kashyyykianHuntingArmorChestPlate = Object:new {

   objectName = "Kashyyykian Hunting Armor Chest Plate", -- name of the lua Object
   stfName = "armor_kashyyykian_hunting_chest_plate", 
   objectCRC = 592867110, 
   groupName = "craftArmorPersonalGroupF", 

   craftingToolTab = 2, 
   --complexity = 45, 
   complexity = 1, 
   size = 1, 

   xpType = "crafting_clothing_armor", 
   xp = 500, 

   assemblySkill = "armor_assembly", 
   experimentingSkill = "armor_experimentation", 

   ingredientTemplateNames = "craft_clothing_ingredients_n, craft_chemical_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n, craft_item_ingredients_n, craft_armor_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n",
   ingredientTitleNames = "auxiliary_coverage, body, liner, hardware_and_attachments, binding_and_reinforcement, padding, structural_reinforcements, armor_segment_kashyyykian_hunting, load_bearing_harness, padding_segment",
   ingredientSlotType = "0, 0, 0, 0, 0, 0, 0, 2, 4, 4",
   resourceTypes = "softwood_evergreen_dathomir, hide_leathery_lok, hide_wooly_tatooine, copper_mythra, petrochem_inert_polymer, fiberplast_naboo, bone_mammal_dantooine, object/tangible/component/armor/shared_armor_segment_kashyyykian_hunting.iff, object/tangible/component/clothing/shared_synthetic_cloth.iff, object/tangible/component/clothing/shared_padding_segment.iff",
   resourceQuantities = "100, 100, 80, 50, 40, 40, 40, 1, 5, 6",
   --resourceQuantities = "100, 100, 80, 50, 40, 40, 40, 4, 5, 6",
   combineTypes = "1, 1, 1, 1, 1, 1, 1, 2, 2, 2",
   contribution = "100, 100, 100, 100, 100, 100, 100, 100, 100, 100",


  numberExperimentalProperties = "1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2",
   experimentalProperties = "XX, XX, XX, XX, OQ, SR, OQ, UT, OQ, MA, OQ, MA, OQ, MA, XX, XX, OQ, SR",
   experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalGroupTitles = "exp_resistance, exp_durability, exp_quality",
   experimentalSubGroupCount = "1, 4, 1",
   experimentalSubGroupTitles = "kineticeffectiveness, armorIntegrity, armor_action_encumbrance, armor_health_encumbrance, armor_mind_encumbrance, base_effectiveness",

   tanoAttributes = "objecttype=257:objectcrc=3776759545:objecttemp=armor_kashyyykian_hunting_chest_plate:templatetype=wearables_name:",
   customizationOptions = "index_color_4, index_color_2, index_color_3, index_color_1",
   customizationDefaults = "0, 0, 0, 0",

   attributesToSet = "base_effectiveness, armorIntegrity, armor_action_encumbrance, armor_health_encumbrance, armor_mind_encumbrance, kineticeffectiveness, specialeffectiveness",
   attributeExperimentalProperties = "exp_quality, exp_durability, exp_durability, exp_durability, exp_durability, exp_resistance, exp_resistance",
   attributePrecision = "10, 0, 0, 0, 0, 10, 10",
   attributesMinMax = "1, 40, 30000, 49000, 68, 42, 250, 151, 25, 16, 1, 35, 1, 35"
}

DraftSchematics:addDraftSchematic(kashyyykianHuntingArmorChestPlate, 592867110)--- Add to global DraftSchematics table
