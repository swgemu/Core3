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


---------------------Male Humanoid Items------------------------------------
mboots = {
	owner = "",

	objectName = "Sturdy Boots",

	templateName = "boots_s05",

	objectCRC = "3277311029",

	objectType = FOOTWEAR,

	equipped = "1"
}

mjacket = {
	owner = "",

	objectName = "Cold Weather Jacket",

	templateName = "jacket_s16",

	objectCRC = "1998242035",

	objectType = JACKET,

	equipped = "1"
}

mshirt = {
	owner = "",

	objectName = "Formfitting Undershirt",

	templateName = "shirt_s14",

	objectCRC = "2618426014",

	objectType = SHIRT,

	equipped = "1"
}

mpants = {
	owner = "",

	objectName = "Large Pocket Pants",

	templateName = "pants_s14",

	objectCRC = "1504671772",

	objectType = PANTS,

	equipped = "1"
}

mshirt = {
	owner = "",

	objectName = "Brawler Shirt",

	templateName = "shirt_s14",

	objectCRC = "2618426014",

	objectType = SHIRT,

	equipped = "1"
}

brawler_humanoid_male_items = {mboots, mjacket, mpants, mshirt}

--------------------------Female Humanoid Items---------------------------

fboots = {
	owner = "",

	objectName = "Sturdy Boots",

	templateName = "boots_s05",

	objectCRC = "3277311029",

	objectType = FOOTWEAR,

	equipped = "1"
}

fshirt = {
	owner = "",

	objectName = "Shortsleeve Shirt",

	templateName = "shirt_s27",

	objectCRC = "1786625409",

	objectType = SHIRT,

	equipped = "1"
}

fpants = {
	owner = "",

	objectName = "Basic Camos",

	templateName = "pants_s07",

	objectCRC = "2576408051",

	objectType = PANTS,

	equipped = "1"
}

fgloves = {
	owner = "",

	objectName = "Cold Weather Gloves",

	templateName = "gloves_s03",

	objectCRC = "745744244",

	objectType = HANDWEAR,

	equipped = "1"
}

brawler_humanoid_female_items = {fshoes, fshirt, fpants, fgloves}


--------------------------Male Trandoshan Items---------------------------

brawler_trandoshan_male_items = {mjacket, mpants, mshirt}

--------------------------Female Trandoshan Items------------------------

brawler_trandoshan_female_items = {fshirt, fpants, fgloves}

--------------------------Male Ithorian Items---------------------------

mipants = {
	owner = "",

	objectName = "Ithorian Reinforced Trousers",

	templateName = "ith_pants_s04",

	objectCRC = "715629952",

	objectType = ITHOGARB,

	equipped = "1"
}

mishirt = {
	owner = "",

	objectName = "Ithorian Frilly Shirt",

	templateName = "ith_shirt_s02",

	objectCRC = "2705445540",

	objectType = ITHOGARB,

	equipped = "1"
}

brawler_ithorian_male_items = {mipants, mishirt}

--------------------------Female Ithorian Items---------------------------

fipants = {
	owner = "",

	objectName = "Ithorian Padded Trousers",

	templateName = "ith_pants_s07",

	objectCRC = "4054846743",

	objectType = ITHOGARB,

	equipped = "1"
}

fishirt = {
	owner = "",

	objectName = "Ithorian Frilly Shirt",

	templateName = "ith_shirt_s02",

	objectCRC = "2705445540",

	objectType = ITHOGARB,

	equipped = "1"
}

figloves = {
	owner = "",

	objectName = "Ithorian Brawling Gloves",

	templateName = "ith_gloves_s01",

	objectCRC = "698134614",

	objectType = ITHOGARB,

	equipped = "1"
}

brawler_ithorian_female_items = {fipants, fishirt, figloves}

brawler_wookie_male_items = { }
brawler_wookie_female_items = { }

-------------------Brawler Items (All Species)--------------------

surv_knife = {
	owner = "",

	objectName = "Survival Knife",

	templateName = "object/weapon/melee/knife/shared_knife_survival.iff",

	objectCRC = 530531036,

	objectType = ONEHANDMELEEWEAPON,

	damageType = WEAPON_KINETIC,

	armorPiercing = WEAPON_NONE,
	
	certification = "",

	equipped = "0"
}

general_brawler_items = {surv_knife}

itemContainer = {
	humanoid_male_items = brawler_humanoid_male_items,
	humanoid_female_items = brawler_humanoid_female_items,
	tran_male_items = brawler_trandoshan_male_items,
	tran_female_items = brawler_trandoshan_female_items,
	itho_male_items = brawler_ithorian_male_items,
	itho_female_items = brawler_ithorian_female_items,
	wook_male_items = brawler_wookie_male_items,
	wook_female_items = brawler_wookie_female_items,
	global_class_items = general_brawler_items
}

addToItemMap("brawler", itemContainer)