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

	objectName = "Dress Shoes",

	templateName = "shoes_s01",

	objectCRC = "3549441025",

	objectType = FOOTWEAR,

	equipped = "1"
}

mpants = {
	
	objectName = "Crafters Pants",

	templateName = "pants_s29",

	objectCRC = "1556581532",

	objectType = PANTS,

	equipped = "1"
}

mshirt = {	

	objectName = "Soft Undershirt",

	templateName = "shirt_s34",

	objectCRC = "2856458350",

	objectType = SHIRT,

	equipped = "1"
}

artisan_humanoid_male_items = {mshoes, mpants, mshirt}

--------------------------Female Humanoid Items---------------------------

fshoes = {
	
	objectName = "Sandals",

	templateName = "shoes_s07",

	objectCRC = "1635672216",

	objectType = FOOTWEAR,

	equipped = "1"
}

fshirt = {
	
	objectName = "Flared Cuff Shirt Shirt",

	templateName = "shirt_s12",

	objectCRC = "788286983",

	objectType = SHIRT,

	equipped = "1"
}

fskirt = {
	
	objectName = "Wrapped Skirt",

	templateName = "skirt_s10",

	objectCRC = "3869787263",

	objectType = SKIRT,

	equipped = "1"
}

artisan_humanoid_female_items = {fshoes, fshirt, fskirt}

--------------------------Male Trandoshan Items---------------------------

artisan_trandoshan_male_items = {mpants, mshirt}

--------------------------Female Trandoshan Items------------------------

artisan_trandoshan_female_items = {fshirt, fskirt}

--------------------------Male Ithorian Items---------------------------

mishirt = {
	
	objectName = "Ithorian Mystic Shirt",

	templateName = "ith_shirt_s10",

	objectCRC = "678629574",

	objectType = ITHOGARB,

	equipped = "1"
}

mipants = {
	
	objectName = "Ithorian Patrol Pants",

	templateName = "ith_pants_s06",

	objectCRC = "3099421338",

	objectType = ITHOGARB,

	equipped = "1"
}

mivest = {	

	objectName = "Ithorian Dress Vest",

	templateName = "ith_vest_s02",

	objectCRC = "3100594389",

	objectType = ITHOGARB,

	equipped = "1"
}

artisan_ithorian_male_items = {mipants, mishirt, mivest}

--------------------------Female Ithorian Items---------------------------

fipants = {
	
	objectName = "Ithorian Patrol Pants",

	templateName = "ith_pants_s06",

	objectCRC = "3099421338",

	objectType = ITHOGARB,

	equipped = "1"
}

fishirt = {
	
	objectName = "Ithorian Striped Shirt",

	templateName = "ith_shirt_s05",

	objectCRC = "1520630192",

	objectType = ITHOGARB,

	equipped = "1"
}

fivest = {
	
	objectName = "Ithorian Dress Vest",

	templateName = "ith_vest_s02",

	objectCRC = "3100594389",

	objectType = ITHOGARB,

	equipped = "1"
}

artisan_ithorian_female_items = {fipants, fishirt, fivest}

--------------------------Wookiee Items---------------------------

artisan_wookie_male_items = { }
artisan_wookie_female_items = { }

-------------------Artisan Items (All Species)--------------------

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

general_artisan_items = {cdef_pistol, surv_knife}


createItemsFromList("artisan", "humanoid", "male", artisan_humanoid_male_items)
createItemsFromList("artisan", "humanoid", "female", artisan_humanoid_female_items)
createItemsFromList("artisan", "trandoshan", "male", artisan_trandoshan_male_items)
createItemsFromList("artisan", "trandoshan", "female", artisan_trandoshan_female_items)
createItemsFromList("artisan", "ithorian", "male", artisan_ithorian_male_items)
createItemsFromList("artisan", "ithorian", "female", artisan_ithorian_female_items)
createItemsFromList("artisan", "wookiee", "male", artisan_wookie_male_items)
createItemsFromList("artisan", "wookiee", "female", artisan_wookie_female_items)
createItemsFromList("artisan", "all", "both", general_artisan_items)