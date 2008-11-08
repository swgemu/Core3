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
x34Landspeeder = Object:new {

   objectName = "X34 Landspeeder", -- name of the lua Object
   stfName = "landspeeder_x34", 
   objectCRC = 3178368929, 
   groupName = "craftArtisanVehicle", 

   craftingToolTab = 16, 
   complexity = 25, 
   size = 1, 

   xpType = "crafting_general", 
   xp = 1800, 

   assemblySkill = "general_assembly", 
   experimentingSkill = "general_experimentation", 

   ingredientTemplateNames = "craft_spaceship_ingredients_n, craft_spaceship_ingredients_n",
   ingredientTitleNames = "vehicle_body, structural_frame",
   ingredientOptionals = "0, 0",
   resourceTypes = "metal_nonferrous, metal_ferrous",
   --resourceQuantities = "1125, 3125",
   resourceQuantities = "112, 312", --REMOVE THIS AFTER HARVESTERS ARE IMPLEMENTED
   combineTypes = "1, 1",
   contribution = "100, 100",

   numberExperimentalProperties = "1, 1, 1",
   experimentalProperties = "XX, XX, SR",
   experimentalWeights = "1, 1, 1",
   experimentalGroupTitles = "exp_durability",
   experimentalSubGroupCount = "1",
   experimentalSubGroupTitles = "hitPoints",

   tanoAttributes = "objecttype=8388613:objectcrc=905926205:objecttemp=landspeeder_x34:templatetype=monster_name:",
   customizationOptions = 0,


   attributesToSet = "hitPoints",
   attributeExperimentalProperties = "exp_durability",
   attributePrecision = "1",
   attributesMinMax = "1500, 3000"

}

DraftSchematics:addDraftSchematic(x34Landspeeder, 3178368929)--- Add to global DraftSchematics table
