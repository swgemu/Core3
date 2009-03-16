--Copyright (C) 2009 <SWGEmu>


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

energyProtectionArmorLayer = Object:new {

   objectName = "Energy Protection Armor Layer",
   stfName = "armor_layer_energy",
   stfFile = "craft_armor_ingredients_n",
   objectCRC = 4258794187,
   groupName = "craftArmorLightLayersGroupA", -- Group schematic is awarded in (See skills table)

   craftingToolTab = 2, -- (See DraftSchemticImplementation.h)
   complexity = 20, 
   size = 3, 

   xpType = "crafting_clothing_armor", 
   xp = 90, 

   assemblySkill = "armor_assembly", 
   experimentingSkill = "armor_experimentation", 

   ingredientTemplateNames = "craft_armor_ingredients_n, craft_armor_ingredients_n, craft_armor_ingredients_n, craft_armor_ingredients_n",
   ingredientTitleNames = "armor_layer_frame, ablative_damage_absorbtion_medium, energy_sink, second_tier_insulation_medium",
   ingredientSlotType = "0, 0, 0, 0",
   resourceTypes = "metal, petrochem_inert_polymer, gas_inert_known, ore",
   resourceQuantities = "20, 8, 8, 5",
   combineTypes = "0, 0, 0, 0",
   contribution = "100, 100, 100, 100",

   numberExperimentalProperties = "1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 1",
   experimentalProperties = "XX, XX, XX, OQ, SR, OQ, UT, MA, OQ, MA, OQ, MA, OQ, XX, XX, OQ, SR, XX",
   experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalGroupTitles = "null, null, exp_durability, exp_quality, exp_durability, exp_durability, exp_durability, exp_durability, null, null, exp_resistance, null",

   experimentalSubGroupTitles = "null, null, hit_points, armor_effectiveness, armor_integrity, armor_health_encumbrance, armor_action_encumbrance, armor_mind_encumbrance, armor_rating, armor_special_type, armor_special_effectiveness, armor_special_integrity",
   experimentalMin = "0, 0, 1000, 1, 100, 20, 20, 20, 1, 2, 1, 20",
   experimentalMax = "0, 0, 1000, 5, 1000, 0, 0, 0, 1, 2, 15, 50",
   experimentalPrecision = "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0",

   tanoAttributes = "objecttype=262145:objectcrc=2938969271:objecttemp=armor_layer_energy:templatetype=craft_armor_ingredients_n:itemmask=65535:customattributes=specialprotection=energyeffectiveness;:",
   customizationOptions = "",
   customizationDefaults = "",
   customizationSkill = "armor_customization"

}

DraftSchematics:addDraftSchematic(energyProtectionArmorLayer, 4258794187)--- Add to global DraftSchematics table
