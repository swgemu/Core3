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

stunBaton = Object:new {

   objectName = "Stun Baton",
   stfName = "baton_stun",
   objectCRC = 366533914,
   groupName = "craftWeaponMeleeGroupE", -- Group schematic is awarded in (See skills table)

   craftingToolTab = 1, -- (See DraftSchemticImplementation.h)
   complexity = 20, 
   size = 3, 

   xpType = "crafting_weapons_general", 
   xp = 110, 

   assemblySkill = "weapon_assembly", 
   experimentingSkill = "weapon_experimentation", 

   ingredientTemplateNames = "craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n, craft_weapon_ingredients_n",
   ingredientTitleNames = "grip_unit, conductive_strike_face, power_cell_brackets, charge_accumulator, shock_pulsor, reinforcement_core",
   ingredientSlotType = "0, 0, 0, 0, 1, 2",
   resourceTypes = "petrochem_inert_polymer, steel, metal, crystalline_byrothsis, object/tangible/component/item/shared_electronic_power_conditioner.iff, object/tangible/component/weapon/shared_reinforcement_core.iff",
   resourceQuantities = "18, 18, 10, 6, 2, 1",
   combineTypes = "0, 0, 0, 0, 1, 1",
   contribution = "100, 100, 100, 100, 100, 100",

   numberExperimentalProperties = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalProperties = "XX, XX, SR, SR, SR, SR, SR, SR, SR, XX, SR, XX, SR, SR, SR",
   experimentalWeights = "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1",
   experimentalGroupTitles = "null, null, expDamage, expDamage, expDamage, expDamage, exp_durability, expRange, expRange, null, expRange, null, expEffeciency, expEffeciency, expEffeciency",

   experimentalSubGroupTitles = "null, null, mindamage, maxdamage, attackspeed, woundchance, hitpoints, zerorangemod, maxrangemod, midrange, midrangemod, maxrange, attackhealthcost, attackactioncost, attackmindcost",
   experimentalMin = "0, 0, 28, 53, 4.2, 1, 750, -5, -5, 2, -5, 4, 10, 45, 39",
   experimentalMax = "0, 0, 52, 98, 2.9, 3, 1500, 5, 5, 2, 5, 4, 4, 24, 19",
   experimentalPrecision = "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0",

   tanoAttributes = "objecttype=131079:objectcrc=2740869510:objecttemp=baton_stun:templatetype=weapon_name:itemmask=65535:customattributes=damagetype=2;:",
   customizationOptions = "",
   customizationDefaults = "",
   customizationSkill = "weapon_customization"

}

DraftSchematics:addDraftSchematic(stunBaton, 366533914)--- Add to global DraftSchematics table
