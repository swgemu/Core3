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
compositeArmorBoots = Object:new {

   objectName = "Composite Armor Boots", -- name of the lua Object
   stfName = "armor_composite_boots", 
   objectCRC = 1025601885, 
   groupName = "craftArmorPersonalGroupF", 

   craftingToolTab = 2, 
   complexity = 45, 
   size = 4, 

   xpType = "crafting_clothing_armor", 
   xp = 160, 

   assemblySkill = "armor_assembly", 
   experimentingSkill = "armor_experimentation", 

   ingredientTemplateNames = "craft_clothing_ingredients_n, craft_chemical_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n, craft_clothing_ingredients_n",
   ingredientTitleNames = "auxiliary_coverage, body, liner, hardware_and_attachments, binding_and_reinforcement, padding, armor, load_bearing_harness, reinforcement",
   ingredientOptionals = "0, 0, 0, 0, 0, 0, 0, 1, 1",
   resourceTypes = "ore_intrusive, fuel_petrochem_solid_known, fiberplast_naboo, aluminum, copper_beyrllius, hide_wooly, object/tangible/component/armor/shared_armor_segment_composite.iff, object/tangible/component/clothing/shared_synthetic_cloth.iff, object/tangible/component/clothing/shared_reinforced_fiber_panels.iff",
   --resourceQuantities = "50, 50, 25, 30, 20, 20, 2, 1, 1",
   resourceQuantities = "50, 50, 25, 30, 20, 20, 1, 1, 1",
   combineTypes = "1, 1, 1, 1, 1, 1, 3, 3, 3",
   contribution = "100, 100, 100, 100, 100, 100, 100, 100, 100",

   numberExperimentalProperties = "1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2",
   experimentalProperties = "XX, XX, XX, OQ, SR, OQ, UT, OQ, MA, OQ, MA, OQ, MA, XX, XX, OQ, SR",
   experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalGroupTitles = "exp_resistance, exp_durability, exp_quality",
   experimentalSubGroupCount = "1, 4, 1",
   experimentalSubGroupTitles = "electricaleffectiveness, armorIntegrity, armor_action_encumbrance, armor_health_encumbrance, armor_mind_encumbrance, base_effectiveness",

   tanoAttributes = "objecttype=263:objectcrc=3683772891:objecttemp=armor_composite_boots:templatetype=wearables_name:",
    
   attributesToSet = "base_effectiveness, armorIntegrity, armor_action_encumbrance, armor_health_encumbrance, armor_mind_encumbrance,  electricaleffectiveness, specialeffectiveness",
   attributeExperimentalProperties = "exp_quality, exp_durability, exp_durability, exp_durability, exp_durability, exp_resistance, exp_resistance",
   attributePrecision = "10, 0, 0, 0, 0, 10, 10",
   attributesMinMax = "1, 40, 30000, 49000, 68, 42, 250, 151, 25, 16, 1, 35, 1, 35"
}

DraftSchematics:addDraftSchematic(compositeArmorBoots, 1025601885)--- Add to global DraftSchematics table
