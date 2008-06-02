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

mvest = {
	

	objectName = "Cargo Vest",

	templateName = "vest_s09",

	objectCRC = "1904031382",

	objectType = VEST,

	equipped = "1"
}

mpants = {
	

	objectName = "Paramilitary Camos",

	templateName = "pants_s21",

	objectCRC = "489589658",

	objectType = PANTS,

	equipped = "1"
}

mshirt = {
	

	objectName = "Longsleeve Shirt",

	templateName = "shirt_s16",

	objectCRC = "235457924",

	objectType = SHIRT,

	equipped = "1"
}

scout_humanoid_male_items = {mshoes, mvest, mpants, mshirt}

--------------------------Female Humanoid Items---------------------------

fshoes = {
	

	objectName = "Casual Shoes",

	templateName = "shoes_s02",

	objectCRC = "143099030",

	objectType = FOOTWEAR,

	equipped = "1"
}

fshirt = {
	

	objectName = "Lined Workshirt",

	templateName = "shirt_s26",

	objectCRC = "594598412",

	objectType = SHIRT,

	equipped = "1"
}

fpants = {
	

	objectName = "Paramilitary Camos",

	templateName = "pants_s21",

	objectCRC = "489589658",

	objectType = PANTS,

	equipped = "1"
}

scout_humanoid_female_items = {fshoes, fshirt, fpants}

--------------------------Male Trandoshan Items---------------------------

scout_trandoshan_male_items = {mvest, mpants, mshirt}

--------------------------Female Trandoshan Items------------------------

scout_trandoshan_female_items = {fshirt, fpants}

--------------------------Male Ithorian Items---------------------------


--------------------------Male Ithorian Items---------------------------

mishirt = {
	

	objectName = "Ithorian Half Sweater",

	templateName = "ith_shirt_s04",

	objectCRC = "330276413",

	objectType = ITHOGARB,

	equipped = "1"
}

mipants = {
	

	objectName = "Strange Ithorian Pants",

	templateName = "ith_pants_s21",

	objectCRC = "1963875198",

	objectType = ITHOGARB,

	equipped = "1"
}

scout_ithorian_male_items = {mipants, mishirt}

--------------------------Female Ithorian Items---------------------------

scout_ithorian_female_items = {mipants, mishirt}

scout_wookie_male_items = { }
scout_wookie_female_items = { }

-------------------Scout Items (All Species)--------------------

general_scout_items = {cdef_pistol}

createItemsFromList("scout", "humanoid", "male", scout_humanoid_male_items)
createItemsFromList("scout", "humanoid", "female", scout_humanoid_female_items)
createItemsFromList("scout", "trandoshan", "male", scout_trandoshan_male_items)
createItemsFromList("scout", "trandoshan", "female", scout_trandoshan_female_items)
createItemsFromList("scout", "ithorian", "male", scout_ithorian_male_items)
createItemsFromList("scout", "ithorian", "female", scout_ithorian_female_items)
createItemsFromList("scout", "wookiee", "male", scout_wookie_male_items)
createItemsFromList("scout", "wookiee", "female", scout_wookie_female_items)
createItemsFromList("scout", "all", "both", general_scout_items)