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

bofaTreat = Object:new {
  objectName = "Bofa Treat", -- name of the lua Object

  stfName = "",

  name = "Bofa Treat",
  objectCRC = 2207249955,
  groupName = "craftArtisanNewbieGroupA",

  craftingToolTab = 4,
  complexity = 3,
  size = 1, 

  ingredientTemplateNames = "craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n",
  ingredientTitleNames = "frame_assembly, receiver_assembly, grip_assembly, powerhandler, blaster_rifle_barrel",
  ingredientOptionals = "0, 0, 0, 0, 0",
  resourceTypes = "metal, metal_ferrous, metal, object/tangible/component/weapon/shared_blaster_power_handler.iff, object/tangible/component/weapon/shared_blaster_rifle_barrel.iff",
  resourceQuantities = "35, 17, 9, 1, 1",

  numberExperimentalProperties = "1, 1, 2, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 1, 2, 1",

  experimentalProperties = "XX, XX, OQ, CD, OQ, CD, OQ, CD, OQ, CD, XX, OQ, CD, XX, XX, OQ, CD, OQ, CD, OQ, CD, XX, OQ, CD, XX",
  experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",

  experimentalGroupTitles = "exp_damage, exp_durability, exp_efficiency, exp_range",

  tanoAttributes = "objecttype=8202:objectcrc=2010692823:objecttemp=dessert_bofa_treat:",

  attributesToSet = "hitPoints, useModifier",

  attributeExperimentalProperties = "null, exp_effectiveness",

  attributesMinMax = "1000, 1000, -15, 15",

  xpType = "general",
  xp = 42,

  assemblySkill = "general_assembly",
  experimentingSkill = "general_experimentation"
}

DraftSchematics:addDraftSchematic(bofaTreat, 2010692823)--- Add to global DraftSchematics table
