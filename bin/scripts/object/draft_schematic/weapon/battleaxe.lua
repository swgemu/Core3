--Copyright (C) 2010 <SWGEmu>


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


object_draft_schematic_weapon_battleaxe = object_draft_schematic_weapon_shared_battleaxe:new {

   templateType = DRAFTSCHEMATIC,

   customObjectName = "Two-handed Axe",

   groupName = "craftWeaponMeleeGroupB", -- Group schematic is awarded in (See skills table)

   craftingToolTab = 1, -- (See DraftSchemticImplementation.h)
   complexity = 20, 
   size = 4, 

   xpType = "crafting_weapons_general", 
   xp = 135, 

   assemblySkill = "weapon_assembly", 
   experimentingSkill = "weapon_experimentation", 
   customizationSkill = "weapon_customization", 

   ingredientTemplateNames = {"craft_weapon_ingredients_n", "craft_weapon_ingredients_n", "craft_weapon_ingredients_n", "craft_weapon_ingredients_n"},
   ingredientTitleNames = {"axe_head", "shaft", "axe_head_fastener", "reinforcement_core"},
   ingredientSlotType = {0, 0, 0, 2},
   resourceTypes = {"iron", "wood", "steel", "object/tangible/component/weapon/shared_reinforcement_core.iff"},
   resourceQuantities = {35, 25, 8, 1},
   combineTypes = {0, 0, 0, 1},
   contribution = {100, 100, 100, 100},

   numberExperimentalProperties = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   experimentalProperties = {"XX", "XX", "SR", "SR", "SR", "SR", "SR", "SR", "SR", "XX", "SR", "XX", "SR", "SR", "SR"},
   experimentalWeights = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   experimentalGroupTitles = {"null", "null", "expDamage", "expDamage", "expDamage", "expDamage", "exp_durability", "expRange", "expRange", "null", "expRange", "null", "expEffeciency", "expEffeciency", "expEffeciency"},
   experimentalSubGroupTitles = {"null", "null", "mindamage", "maxdamage", "attackspeed", "woundchance", "hitpoints", "zerorangemod", "maxrangemod", "midrange", "midrangemod", "maxrange", "attackhealthcost", "attackactioncost", "attackmindcost"},
   experimentalMin = {0, 0, 53, 88, 5.6, 12, 750, 0, 0, 3, 0, 4, 52, 17, 10},
   experimentalMax = {0, 0, 98, 163, 4.1, 22, 1500, 10, 10, 3, 10, 4, 26, 8, 4},
   experimentalPrecision = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

   tanoCRC = 3657264180, -- Script: 'object/weapon/melee/2h_sword/2h_sword_battleaxe.iff'
}
ObjectTemplates:addTemplate(object_draft_schematic_weapon_battleaxe, "object/draft_schematic/weapon/battleaxe.iff")
