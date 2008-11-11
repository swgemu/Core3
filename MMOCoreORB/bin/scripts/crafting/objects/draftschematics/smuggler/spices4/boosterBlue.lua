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
boosterBlue = Object:new {

   objectName = "Booster Blue", -- name of the lua Object
   stfName = "booster_blue", 
   objectCRC = 1461060097, 
   groupName = "craftSmugglerSpiceD", 

   craftingToolTab = 4, 
   complexity = 13, 
   size = 1, 

   xpType = "crafting_spice", 
   xp = 512, 

   assemblySkill = "spice_assembly", 
   experimentingSkill = "spice_experimentation", 

   ingredientTemplateNames = "craft_food_ingredients_n, craft_food_ingredients_n, craft_food_ingredients_n",
   ingredientTitleNames = "copper_phthalocyanine_blue, dimethylaminobenzene, delivery_mechanism",
   ingredientSlotType = "0, 0, 0",
   resourceTypes = "copper, chemical, metal",
   resourceQuantities = "15, 15, 15",
   combineTypes = "1, 1, 1",
   contribution = "100, 100, 100",


   numberExperimentalProperties = "3",
   experimentalProperties = "DR, OQ, UT",
   experimentalWeights = "4, 1, 1",
   experimentalGroupTitles = "exp_nutrition",
   experimentalSubGroupCount = "1",
   experimentalSubGroupTitles = "decayRate",

   tanoAttributes = "objecttype=8202:objectcrc=2516008025:objecttemp=spice_booster_blue:templatetype=spice:",
   customizationOptions = "",
   customizationDefaults = "",

   attributesToSet = "decayRate, health, healthtime, action",
   attributeExperimentalProperties = "exp_nutrition, exp_nutrition, exp_nutrition, exp_nutrition",
   attributePrecision = "0, 0, 0 ,0",
   attributesMinMax = "0, 0, 1000, 1000, 780, 780, 400, 400"

}

DraftSchematics:addDraftSchematic(boosterBlue, 1461060097)--- Add to global DraftSchematics table
