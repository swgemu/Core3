--Copyright (C) 2007 <SWGEmu>
 
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

blasterRifleBarrel = Object:new {
  objectName = "Blaster Rifle Barrel", -- name of the lua Object

  stfName = "",

  name = "Blaster Rifle Barrel",
  objectCRC = 3017432687,
  groupName = "craftWeaponRangedGroupA",

  craftingToolTab = 1,
  complexity = 5,
  size = 1, 

  xpType = "crafting_weapons_general",
  xp = 20,

  assemblySkill = "weapon_assembly",
  experimentingSkill = "weapon_experimentation",

  ingredientTemplateNames = "craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n",
  ingredientTitleNames = "module_assembly, xciter_circuitry, circuitry_substrate, gas_containment_unit, reactant_source",
  ingredientSlotType = "0, 0, 0, 0, 0",
  --resourceTypes = "petrochem_inert, copper, ore, metal, gas_reactive",
resourceTypes = "metal, metal, metal, metal, metal",
  resourceQuantities = "12, 3, 3, 5, 10",
  combineTypes = "1, 1, 1, 1, 1",
  contribution = "100, 100, 100, 100, 100",

  numberExperimentalProperties = "1, 1, 1, 2, 2, 2, 1, 2",
  experimentalProperties = "XX, XX, XX, CD, OQ, CD, OQ, CD, OQ, XX, CD, OQ",
  experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",

  experimentalGroupTitles = "expdamage, expdurability",

  experimentalSubGroupCount = "3, 1",

  experimentalSubGroupTitles = "speed, maxDamage, minDamage, hitpoints",

  tanoAttributes = "objecttype=262144:objectcrc=260681278:objecttemp=blaster_rifle_barrel:templatetype=obj_n:",
  customizationOptions = "",
   customizationDefaults = "",

  attributesToSet = "speed, maxDamage, minDamage, hitpoints",

  attributeExperimentalProperties = "expdamage, expdamage, expdamage, expdurability",

  attributePrecision = "1, 1, 1, 0",
  attributesMinMax = "1, 5, 2, 6, 3, 7, 1, 1000"

}

DraftSchematics:addDraftSchematic(blasterRifleBarrel, 3017432687)--- Add to global DraftSchematics table
