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
mshoes = {
	

	objectName = "Casual Shoes",

	templateName = "shoes_s02",

	objectCRC = "143099030",

	objectType = FOOTWEAR,

	equipped = "1"
}

mjacket = {
	

	objectName = "Sleeveless Jacket",

	templateName = "jacket_s24",

	objectCRC = "3363313761",

	objectType = JACKET,

	equipped = "1"
}

mpants = {
	

	objectName = "Work Slacks",

	templateName = "pants_s12",

	objectCRC = "3946919045",

	objectType = PANTS,

	equipped = "1"
}

mshirt = {
	

	objectName = "Reinforced Work Shirt",

	templateName = "shirt_s10",

	objectCRC = "3169222941",

	objectType = SHIRT,

	equipped = "1"
}

medic_humanoid_male_items = {mshoes, mjacket, mpants, mshirt}

--------------------------Female Humanoid Items---------------------------

fboots = {
	

	objectName = "Hide Boots",

	templateName = "boots_s04",

	objectCRC = "2321198008",

	objectType = FOOTWEAR,

	equipped = "1"
}

fbodysuit = {
	

	objectName = "Reinforced Jumpsuit",

	templateName = "bodysuit_s13",

	objectCRC = "1492714777",

	objectType = BODYSUIT,

	equipped = "1"
}

medic_humanoid_female_items = {fboots, fbodysuit}

--------------------------Male Trandoshan Items---------------------------

medic_trandoshan_male_items = {mjacket, mpants, mshirt}

--------------------------Female Trandoshan Items------------------------

medic_trandoshan_female_items = {fbodysuit}

--------------------------Male Ithorian Items---------------------------

mijacket = {
	

	objectName = "Ithorian Med Team Jacket",

	templateName = "ith_jacket_s05",

	objectCRC = "3954881783",

	objectType = ITHOGARB,

	equipped = "1"
}

mipants = {
	

	objectName = "Ithorian Cargo Pants",

	templateName = "ith_pants_s12",

	objectCRC = "2204230753",

	objectType = ITHOGARB,

	equipped = "1"
}

mishirt = {
	

	objectName = "Ithorian Easy Fit Shirt",

	templateName = "ith_shirt_s05",

	objectCRC = "1520630192",

	objectType = ITHOGARB,

	equipped = "1"
}

medic_ithorian_male_items = {mijacket, mipants, mishirt}

--------------------------Female Ithorian Items---------------------------

fipants = {
	

	objectName = "Ithorian Striped Pants",

	templateName = "ith_pants_s03",

	objectCRC = "3510931092",

	objectType = ITHOGARB,

	equipped = "1"
}

fishirt = {
	

	objectName = "Ithorian Long Sweater",

	templateName = "ith_shirt_s01",

	objectCRC = "2052487731",

	objectType = ITHOGARB,

	equipped = "1"
}

medic_ithorian_female_items = {fipants, fishirt}

medic_wookie_male_items = { }
medic_wookie_female_items = { }

-------------------Medic Items (All Species)--------------------

cdef_pistol = {
	

	objectName = "CDEF Pistol",

	templateName = "object/weapon/ranged/pistol/shared_pistol_cdef.iff",

	objectCRC = 937103853,

	objectType = PISTOL,

	damageType = WEAPON_ENERGY,

	armorPiercing = WEAPON_NONE,
	
	certification = "",

	equipped = "0"
}

surv_knife = {
	

	objectName = "Survival Knife",

	templateName = "object/weapon/melee/knife/shared_knife_survival.iff",

	objectCRC = 530531036,

	objectType = ONEHANDMELEEWEAPON,

	damageType = WEAPON_KINETIC,

	armorPiercing = WEAPON_NONE,
	
	certification = "",

	equipped = "0"
}

general_medic_items = {cdef_pistol, surv_knife}

createItemsFromList("medic", "humanoid", "male", medic_humanoid_male_items)
createItemsFromList("medic", "humanoid", "female", medic_humanoid_female_items)
createItemsFromList("medic", "trandoshan", "male", medic_trandoshan_male_items)
createItemsFromList("medic", "trandoshan", "female", medic_trandoshan_female_items)
createItemsFromList("medic", "ithorian", "male", medic_ithorian_male_items)
createItemsFromList("medic", "ithorian", "female", medic_ithorian_female_items)
createItemsFromList("medic", "wookiee", "male", medic_wookie_male_items)
createItemsFromList("medic", "wookiee", "female", medic_wookie_female_items)
createItemsFromList("medic", "all", "both", general_medic_items)