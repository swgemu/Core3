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

-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
alever_twethpek = {
	
	objectName = "Alever Tweth'pek",

	templateName = "object/tangible/food/foraged/shared_foraged_fruit_s3.iff",
        
        healthBonus = 0,
        actionBonus = 100,
        mindBonus = 25,

        duration = 100,

	objectCRC = 3506644976,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
} 

CreateForageItemFromLua(alever_twethpek);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
etostew_zann = {
	
	objectName = "Etost'Ew Zann",

	templateName = "object/tangible/food/foraged/shared_foraged_vegetable_s4.iff",
        
        healthBonus = 50,
        ActionBonus = 50,
        MindBonus = 50,
        
        duration = 700,

	objectCRC = 1064337473,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(etostew_zann);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
flurrcle_onion = {

	objectName = "Flurr-Cle Onion",

	templateName = "object/tangible/food/foraged/shared_foraged_vegetable_s3.iff",
        
        healthBonus = 0,
        actionBonus = 0,
        mindBonus = 500,
        
        duration = 60,

	objectCRC = 3298011989,

	objectType = FOOD,  

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(flurrcle_onion);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
jar_of_foraged_berries = {
	
	objectName = "Jar of Foraged Berries",

	templateName = "object/tangible/food/foraged/shared_edible_jar_berries.iff",
        
        healthBonus = 100,
        actionBonus = 0,
        mindBonus = 0,
        
        duration = 300,

	objectCRC = 1405655823,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items       
}

CreateForageItemFromLua(jar_of_foraged_berries);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
jar_of_foraged_bugs = {
	
	objectName = "Jar of Foraged Bugs",

	templateName = "object/tangible/food/foraged/shared_edible_jar_bugs.iff",
        
        healthBonus = 0,
        actionBonus = 100,
        mindBonus = 0,
        
        duration = 300,

	objectCRC = 2220813342,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(jar_of_foraged_bugs);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
jar_of_foraged_grubs = {

	objectName = "Jar of Foraged Grubs",

	templateName = "object/tangible/food/foraged/shared_edible_jar_funk.iff",
        
        healthBonus = 0,
        actionBonus = 0,
        mindBonus = 100,
        
        duration = 300,

	objectCRC = 3997953331,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(jar_of_foraged_grubs);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
jar_of_foraged_livers = {
	
	objectName = "Jar of Foraged Livers",

	templateName = "object/tangible/food/foraged/shared_edible_jar_livers.iff",
        
        healthBonus = 100,
        actionBonus = 50,
        mindBonus = 0,
        
        duration = 250,

	objectCRC = 4279994826,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(jar_of_foraged_livers);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
jar_of_foraged_fungus = {

	objectName = "Jar of Foraged Fungus",

	templateName = "object/tangible/food/foraged/shared_edible_jar_fungus.iff",
        
        healthBonus = 50,
        actionBonus = 0,
        mindBonus = 100,
        
        duration = 250,

	objectCRC = 404667969,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(jar_of_foraged_fungus);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
kodo_fruit = {
	
	objectName = "Ko-Do Fruit",

	templateName = "object/tangible/food/foraged/shared_foraged_fruit_s4.iff",
        
        healthBonus = 0,
        actionBonus = 50,
        mindBonus = 50,
        
        duration = 250,

	objectCRC = 719326436,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(kodo_fruit);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
maroj_melon = {

	objectName = "Maroj Melon",

	templateName = "object/tangible/food/foraged/shared_foraged_fruit_s1.iff",

        healthBonus = 50,
        actionBonus = 0,
        mindBonus = 50,
        
        duration = 150,

	objectCRC = 1125771498,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(maroj_melon);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
schule_nef = {

	objectName = "Schule Nef",

	templateName = "object/tangible/food/foraged/shared_foraged_vegetable_s2.iff",

        healthBonus = 0,
        actionBonus = 0,
        mindBonus = 50,
        
        duration = 400,

	objectCRC = 2375994584,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(schule_nef);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
sijjo_sewi = {

	objectName = "Sijjo Sewi",

	templateName = "object/tangible/food/foraged/shared_foraged_fruit_s5.iff",

        healthBonus = 0,
        actionBonus = 100,
        mindBonus = 0,
        
        duration = 200,

	objectCRC = 1676503913,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(sijjo_sewi);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
sosi_hodor = {

	objectName = "Sosi Hodor",

	templateName = "object/tangible/food/foraged/shared_foraged_vegetable_s5.iff",

        healthBonus = 120,
        actionBonus = 0,
        mindBonus = 50,
        
        duration = 400,

	objectCRC = 1987962828,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(sosi_hodor);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
wild_snaff = {
	
	objectName = "Wild Snaff",

	templateName = "object/tangible/food/foraged/shared_foraged_fruit_s2.iff",

        healthBonus = 50,
        actionBonus = 50,
        mindBonus = 50,
        
        duration = 50,

	objectCRC = 2551070845,

	objectType = FOOD,

        forageGroup = 1 -- basic forage items
}

CreateForageItemFromLua(wild_snaff);
-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------
