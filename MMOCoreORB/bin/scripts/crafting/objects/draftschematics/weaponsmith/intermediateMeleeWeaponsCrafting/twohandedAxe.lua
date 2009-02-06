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

twohandedAxe = Object:new {

   objectName = "Two-handed Axe",
   stfName = "sword_2h_axe",
   objectCRC = 597539800,
   groupName = "craftWeaponMeleeGroupB", -- Group schematic is awarded in (See skills table)

   craftingToolTab = 1, -- (See DraftSchemticImplementation.h)
   complexity = 20, 
   size = 4, 

   xpType = "crafting_weapons_general", 
   xp = 135, 

   assemblySkill = "weapon_assembly", 
   experimentingSkill = "weapon_experimentation", 

   ingredientTemplateNames = "craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n",
   ingredientTitleNames = "axe_head, shaft, axe_head_fastener, reinforcement_core",
   ingredientSlotType = "0, 0, 0, 2",
   resourceTypes = "iron, wood, steel, object/tangible/component/weapon/shared_reinforcement_core.iff",
   resourceQuantities = "35, 25, 8, 1",
   combineTypes = "0, 0, 0, 1",
   contribution = "100, 100, 100, 100",

   numberExperimentalProperties = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalProperties = "XX, XX, SR, SR, SR, SR, SR, SR, SR, XX, SR, XX, SR, SR, SR",
   experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalGroupTitles = "null, null, expDamage, expDamage, expDamage, expDamage, exp_durability, expRange, expRange, null, expRange, null, expEffeciency, expEffeciency, expEffeciency",

   experimentalSubGroupTitles = "null, null, mindamage, maxdamage, attackspeed, woundchance, hitpoints, zerorangemod, maxrangemod, midrange, midrangemod, maxrange, attackhealthcost, attackactioncost, attackmindcost",
   experimentalMin = "0, 0, 53, 88, 5.6, 12, 750, 0, 0, 3, 0, 4, 52, 17, 10",
   experimentalMax = "0, 0, 98, 163, 4.1, 22, 1500, 10, 10, 3, 10, 4, 26, 8, 4",
   experimentalPrecision = "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0",

   tanoAttributes = "objecttype=131080:objectcrc=3488117788:objecttemp=sword_2h_axe:templatetype=weapon_name:itemmask=65535:customattributes=damagetype=1;:",
   customizationOptions = "",
   customizationDefaults = "",
   customizationSkill = "weapon_customization"

}

DraftSchematics:addDraftSchematic(twohandedAxe, 597539800)--- Add to global DraftSchematics table
