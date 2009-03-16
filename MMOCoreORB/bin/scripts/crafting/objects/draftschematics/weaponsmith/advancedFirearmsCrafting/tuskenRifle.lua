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

tuskenRifle = Object:new {

   objectName = "Tusken Rifle",
   stfName = "rifle_tusken",
   stfFile = "weapon_name",
   objectCRC = 112067557,
   groupName = "craftWeaponRangedGroupC", -- Group schematic is awarded in (See skills table)

   craftingToolTab = 1, -- (See DraftSchemticImplementation.h)
   complexity = 16, 
   size = 3, 

   xpType = "crafting_weapons_general", 
   xp = 110, 

   assemblySkill = "weapon_assembly", 
   experimentingSkill = "weapon_experimentation", 

   ingredientTemplateNames = "craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n",
   ingredientTitleNames = "frame_assembly, receiver_assembly, grip_assembly, feed_unit, barrel, scope, stock",
   ingredientSlotType = "0, 0, 0, 2, 2, 4, 4",
   resourceTypes = "iron, metal_ferrous, metal, object/tangible/component/weapon/shared_projectile_feed_mechanism.iff, object/tangible/component/weapon/shared_projectile_rifle_barrel.iff, object/tangible/component/weapon/shared_scope_weapon.iff, object/tangible/component/weapon/shared_stock.iff",
   resourceQuantities = "35, 14, 7, 1, 1, 1, 1",
   combineTypes = "0, 0, 0, 1, 1, 1, 1",
   contribution = "100, 100, 100, 100, 100, 100, 100",

   numberExperimentalProperties = "1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2",
   experimentalProperties = "XX, XX, CD, OQ, CD, OQ, CD, OQ, CD, OQ, CD, OQ, CD, OQ, XX, XX, XX, CD, OQ, CD, OQ, CD, OQ, CD, OQ",
   experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalGroupTitles = "null, null, expDamage, expDamage, expDamage, expDamage, expEffeciency, exp_durability, null, null, null, expRange, expEffeciency, expEffeciency, expEffeciency",

   experimentalSubGroupTitles = "null, null, mindamage, maxdamage, attackspeed, woundchance, roundsused, hitpoints, zerorangemod, maxrangemod, midrange, midrangemod, attackhealthcost, attackactioncost, attackmindcost",
   experimentalMin = "0, 0, 70, 105, 9.1, 6, 30, 750, -60, -50, 60, 14, 13, 23, 55",
   experimentalMax = "0, 0, 130, 195, 6.3, 12, 65, 1500, -60, -50, 60, 26, 7, 13, 30",
   experimentalPrecision = "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0",

   tanoAttributes = "objecttype=131084:objectcrc=2874182418:objecttemp=rifle_tusken:templatetype=weapon_name:itemmask=65535:customattributes=damagetype=1;:",
   customizationOptions = "",
   customizationDefaults = "",
   customizationSkill = "weapon_customization"

}

DraftSchematics:addDraftSchematic(tuskenRifle, 112067557)--- Add to global DraftSchematics table
