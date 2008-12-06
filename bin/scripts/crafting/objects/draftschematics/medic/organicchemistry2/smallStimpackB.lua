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
smallStimpackB = Object:new {

   objectName = "Small Stimpack  B", -- name of the lua Object
   stfName = "stimpack_sm_s1_b", 
   objectCRC = 82684935, 
   groupName = "craftMedicineStimpackGroupB", 

   craftingToolTab = 64, 
   complexity = 18, 
   size = 3, 

   xpType = "crafting_medicine_general", 
   xp = 52, 

   assemblySkill = "medicine_assembly", 
   experimentingSkill = "medicine_experimentation", 

   ingredientTemplateNames = "craft_chemical_ingredients_n, craft_chemical_ingredients_n, craft_chemical_ingredients_n, craft_chemical_ingredients_n, craft_chemical_ingredients_n",
   ingredientTitleNames = "inorganic_element, organic_element, drug_strength_compound, drug_duration_compound, delivery_medium",
   ingredientSlotType = "0, 0, 2, 2, 2",
   resourceTypes = "inorganic, organic, object/tangible/component/chemistry/shared_biologic_effect_controller.iff, object/tangible/component/chemistry/shared_release_mechanism_duration.iff, object/tangible/component/chemistry/shared_liquid_delivery_suspension.iff",
   resourceQuantities = "12, 12, 1, 1, 1",
   combineTypes = "1, 1, 3, 3, 3",
   contribution = "100, 100, 33, 33, 33",

   numberExperimentalProperties = "1, 1, 2, 2",
   experimentalProperties = "XX, XX, OQ, PE, OQ, UT",
   experimentalWeights = "1, 1, 2, 1, 2, 1",
   experimentalGroupTitles = "exp_effectiveness, exp_charges",
   experimentalSubGroupCount = "1, 1",
   experimentalSubGroupTitles = "power, charges",

   tanoAttributes = "objecttype=8205:objectcrc=1264058526:objecttemp=stimpack_sm_s1_b:templatetype=medicine_name:",
   customizationOptions = "",
   customizationDefaults = "",

   attributesToSet = "charges, power, medicineUseRequired",
   attributeExperimentalProperties = "exp_charges, exp_effectiveness, exp_effectiveness",
   attributePrecision = "0, 0, 0",
   attributesMinMax = "10, 35, 75, 500, 5, 5"

}

DraftSchematics:addDraftSchematic(smallStimpackB, 82684935)--- Add to global DraftSchematics table
