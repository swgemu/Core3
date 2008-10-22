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

dlt20Rifle = Object:new {
  objectName = "DLT20 Rifle", -- name of the lua Object

  stfName = "",

  name = "DLT20 Rifle",
  objectCRC = 1869102319,
  groupName = "craftArtisanNewbieGroupA",

  craftingToolTab = 1,
  complexity = 21,
  size = 3, 
  
  xpType = "crafting_weapons_general",
  xp = 42,

  assemblySkill = "weapon_assembly",
  experimentingSkill = "weapon_experimentation",

  ingredientTemplateNames = "craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n",
  ingredientTitleNames = "frame_assembly, receiver_assembly, grip_assembly, powerhandler, barrel",
  ingredientOptionals = "0, 0, 0, 0, 0",
  --resourceTypes = "metal, metal_ferrous, metal, object/tangible/component/weapon/shared_blaster_power_handler.iff, object/tangible/component/weapon/shared_blaster_rifle_barrel.iff",
 resourceTypes = "metal, metal, metal, metal, metal",

  resourceQuantities = "35, 17, 9, 1, 1",
  combineTypes = "1, 1, 1, 1, 1",
  contribution = "100, 100, 100, 100, 100",

  numberExperimentalProperties = "1, 1, 2, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 2, 2",
  experimentalProperties = "XX, XX, OQ, CD, OQ, CD, OQ, CD, OQ, CD, XX, OQ, CD, XX, XX, XX, OQ, CD, OQ, CD, OQ, CD, OQ, CD",
  experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
  experimentalGroupTitles = "expdamage, expdurability, expeffeciency, exprange",
  experimentalSubGroupCount = "4, 1, 3, 1",
  experimentalSubGroupTitles = "speed, maxDamage, minDamage, wound, decay, actionCost, healthCost, mindCost, range",

  tanoAttributes = "objecttype=131084:objectcrc=2200111432:objecttemp=rifle_blaster_dlt20a:",
  
  attributesToSet = "speed, maxDamage, minDamage, wound, hitPoints, useModifier",
  attributeExperimentalProperties = "expdamage, expdamage, expdamage, expdamage, expdurability, expeffeciency, expeffeciency, expeffeciency, exprange",
  attributePrecision = "0, 0, 0, 0, 0, 0, 0, 0, 0",
  attributesMinMax = "4.5, 7.5, 150, 230, 55, 130, 5, 20, 0, 1000, 10, 40, 15, 45, 15, 43, 50, 65",

}

DraftSchematics:addDraftSchematic(dlt20Rifle, 1869102319)--- Add to global DraftSchematics table
