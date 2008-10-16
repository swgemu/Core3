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

--1505349903 & 753735496

structureCraftingTool = Object:new {
  objectName = "Structure and Furniture Crafting Tool", -- name of the lua Object

  stfName = "",

  name = "Structure and Furniture Crafting Tool",
  objectCRC = 1567438265,
  groupName = "craftArtisanNewbieGroupA",

  craftingToolTab = 4096,
  complexity = 11,
  size = 2,

  xpType = "crafting_general",
  xp = 25,

  assemblySkill = "general_assembly",
  experimentingSkill = "general_experimentation",

  ingredientTemplateNames = "craft_item_ingredients_n, craft_item_ingredients_n, craft_item_ingredients_n",
  ingredientTitleNames = "assembly_enclosure, thermal_shielding, electronic_control_unit",
  ingredientOptionals = "0, 0, 0",
  resourceTypes = "metal, mineral, chemical",
  resourceQuantities = "16, 8, 10",
  combineTypes = "1, 1, 1",

  numberExperimentalProperties = "1, 1, 1, 1",

  experimentalProperties = "XX, XX, XX, CD",
  experimentalWeights = "0, 0, 0, 1",

  experimentalGroupTitles = "exp_effectiveness",

  experimentalSubGroupCount = "1",

  experimentalSubGroupTitles = "useModifier",

  tanoAttributes = "objecttype=32769:objectcrc=4275700789:objecttemp=structure_tool_name:templatetype=crafting:",
  
  attributesToSet = "useModifier",
  attributeExperimentalProperties = "exp_effectiveness",
  attributePrecision = "2",
  attributesMinMax = "-15, 15"

}

DraftSchematics:addDraftSchematic(structureCraftingTool, 1567438265) --- Add to global DraftSchematics table
