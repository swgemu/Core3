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


-------------------Male Humanoid Items------------------------------------
mboots = {
	

	objectName = "Paneled Boots",

	templateName = "boots_s21",

	objectCRC = "3589494086",

	objectType = FOOTWEAR,

	equipped = "1"
}

mjacket = {
	

	objectName = "Padded Jacket",

	templateName = "jacket_s05",

	objectCRC = "3072681244",

	objectType = JACKET,

	equipped = "1"
}

mpants = {
	

	objectName = "Pocketed Work Pants",

	templateName = "pants_s04",

	objectCRC = "1116173668",

	objectType = PANTS,

	equipped = "1"
}

marksman_humanoid_male_items = {mboots, mjacket, mpants}

--------------------------Female Humanoid Items---------------------------

fshoes = {
	

	objectName = "Casual Shoes",

	templateName = "shoes_s02",

	objectCRC = "143099030",

	objectType = FOOTWEAR,

	equipped = "1"
}

fshirt = {
	

	objectName = "Sports Wrap",

	templateName = "shirt_s24",

	objectCRC = "2976519446",

	objectType = SHIRT,

	equipped = "1"
}

fpants = {
	

	objectName = "Pantaloons",

	templateName = "pants_s24",

	objectCRC = "1960275860",

	objectType = PANTS,

	equipped = "1"
}

fvest = {
	

	objectName = "Mangy Vest",

	templateName = "vest_s10",

	objectCRC = "1655790437",

	objectType = VEST,

	equipped = "1"
}

marksman_humanoid_female_items = {fshoes, fshirt, fpants, fvest}

--------------------------Male Trandoshan Items---------------------------

marksman_trandoshan_male_items = {mpants, mjacket}

--------------------------Female Trandoshan Items------------------------

marksman_trandoshan_female_items = {fshirt, fpants, fvest}

--------------------------Male Ithorian Items---------------------------

mijacket = {
	

	objectName = "Ithorian Cargo Jacket",

	templateName = "ith_jacket_s02",

	objectCRC = "274309091",

	objectType = ITHOGARB,

	equipped = "1"
}

mipants = {
	

	objectName = "Ithorian Camos",

	templateName = "ith_pants_s05",

	objectCRC = "1672135181",

	objectType = ITHOGARB,

	equipped = "1"
}

mishirt = {
	

	objectName = "Ithorian Tight Fit Shirt",

	templateName = "ith_shirt_s12",

	objectCRC = "3127500764",

	objectType = ITHOGARB,

	equipped = "1"
}

marksman_ithorian_male_items = {mijacket, mipants, mishirt}

--------------------------Female Ithorian Items---------------------------

marksman_ithorian_female_items = {mipants, mishirt}

marksman_wookie_male_items = { }
marksman_wookie_female_items = { }

----------------------Marksman Items (All Species)------------------------

general_marksman_items = {cdef_pistol, cdef_carbine, cdef_rifle}

createItemsFromList("marksman", "humanoid", "male", marksman_humanoid_male_items)
createItemsFromList("marksman", "humanoid", "female", marksman_humanoid_female_items)
createItemsFromList("marksman", "trandoshan", "male", marksman_trandoshan_male_items)
createItemsFromList("marksman", "trandoshan", "female", marksman_trandoshan_female_items)
createItemsFromList("marksman", "ithorian", "male", marksman_ithorian_male_items)
createItemsFromList("marksman", "ithorian", "female", marksman_ithorian_female_items)
createItemsFromList("marksman", "wookiee", "male", marksman_wookie_male_items)
createItemsFromList("marksman", "wookiee", "female", marksman_wookie_female_items)
createItemsFromList("marksman", "all", "both", general_marksman_items)