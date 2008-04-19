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
mchestplate = {
	

	objectName = "Composite Chestplate",

	templateName = "armor_composite_chestplate",

	objectCRC = 2068279078,

	objectType = BODYARMOR,

	armorType = ARMOR_CHEST,

	equipped = "0"
}

mhelmet = {
	

	objectName = "Composite Helmet",

	templateName = "armor_composite_helmet",

	objectCRC = 2599755434,

	objectType = HEADARMOR,

	armorType = ARMOR_HEAD,

	equipped = "0"
}

mboots = {
	

	objectName = "Composite Boots",

	templateName = "armor_composite_boots",

	objectCRC = 3683772891,

	objectType = FOOTARMOR,

	armorType = ARMOR_FOOT,

	equipped = "0"
}

mgloves = {
	

	objectName = "Composite Gloves",

	templateName = "armor_composite_gloves",

	objectCRC = 741736354,

	objectType = HANDARMOR,
	
	armorType = ARMOR_HAND,

	equipped = "0"
}

mleggings = {
	

	objectName = "Composite Leggings",

	templateName = "armor_composite_leggings",

	objectCRC = 3264529458,

	objectType = LEGARMOR,

	armorType = ARMOR_LEG,

	equipped = "0"
}

mbicepl = {
	

	objectName = "Composite Bicep",

	templateName = "armor_composite_bicep_l",

	objectCRC = 329570833,

	objectType = ARMARMOR,

	armorType = ARMOR_BICEPL,

	equipped = "0"
}

mbicepr = {
	

	objectName = "Composite Bicep",

	templateName = "armor_composite_bicep_r",

	objectCRC = 1668390786,

	objectType = ARMARMOR,

	armorType = ARMOR_BICEPR,

	equipped = "0"
}

mbracerl = {
	

	objectName = "Composite Bracer",

	templateName = "armor_composite_bracer_l",

	objectCRC = 1303386413,

	objectType = ARMARMOR,

	armorType = ARMOR_BRACERL,

	equipped = "0"
}

mbracerr = {
	

	objectName = "Composite Bracer",

	templateName = "armor_composite_bracer_r",

	objectCRC = 1030053054,

	objectType = ARMARMOR,

	armorType = ARMOR_BRACERR,

	equipped = "0"
}

general_humanoid_male_items = {mchestplate, mboots, mgloves, mleggings, mhelmet, mbracerr, mbracerl, mbicepl, mbicepr}


--------------------------Female Humanoid Items---------------------------

general_humanoid_female_items = {mchestplate, mboots, mgloves, mleggings, mhelmet, mbracerr, mbracerl, mbicepl, mbicepr}

----------------------------Male Trandoshan Items---------------------------

general_trandoshan_male_items = {mchestplate, mgloves, mleggings, mhelmet, mbracerr, mbracerl, mbicepl, mbicepr}

--------------------------Female Trandoshan Items---------------------------

general_trandoshan_female_items = {mchestplate, mgloves, mleggings, mhelmet, mbracerr, mbracerl, mbicepl, mbicepr}

--------------------------Male Ithorian Items---------------------------

ichestplate = {
	

	objectName = "Ithorian Sentinel Armor Chestplate",

	templateName = "ith_armor_s03_chest_plate",

	objectCRC = 379409880,

	objectType = BODYARMOR,

	armorType = ARMOR_CHEST,

	equipped = "0"
}

ihelmet = {
	

	objectName = "Ithorian Sentinel Armor Helmet",

	templateName = "ith_armor_s03_helmet",

	objectCRC = 618689855,

	objectType = HEADARMOR,

	armorType = ARMOR_HEAD,

	equipped = "0"
}

iboots = {
	

	objectName = "Ithorian Sentinel Armor Boots",

	templateName = "ith_armor_s03_boots",

	objectCRC = 3974465933,

	objectType = FOOTARMOR,

	armorType = ARMOR_FOOT,

	equipped = "0"
}

igloves = {
	

	objectName = "Ithorian Sentinel Armor Gloves",

	templateName = "ith_armor_s03_gloves",

	objectCRC = 2451608631,

	objectType = HANDARMOR,
	
	armorType = ARMOR_HAND,

	equipped = "0"
}

ileggings = {
	

	objectName = "Ithorian Sentinel Armor Leggings",

	templateName = "ith_armor_s03_leggings",

	objectCRC = 792067440,

	objectType = LEGARMOR,

	armorType = ARMOR_LEG,

	equipped = "0"
}

ibicepl = {
	

	objectName = "Ithorian Sentinel Armor Bicep",

	templateName = "ith_armor_s03_bicep_l",

	objectCRC = 2273272421,

	objectType = ARMARMOR,

	armorType = ARMOR_BICEPL,

	equipped = "0"
}

ibicepr = {
	

	objectName = "Ithorian Sentinel Armor Bicep",

	templateName = "ith_armor_s03_bicep_r",

	objectCRC = 4155123702,

	objectType = ARMARMOR,

	armorType = ARMOR_BICEPR,

	equipped = "0"
}

ibracerl = {
	

	objectName = "Ithorian Sentinel Armor Bracer",

	templateName = "ith_armor_s03_bracer_l",

	objectCRC = 2685476975,

	objectType = ARMARMOR,

	armorType = ARMOR_BRACERL,

	equipped = "0"
}

imbracerr = {
	

	objectName = "Ithorian Sentinel Armor Bracer",

	templateName = "ith_armor_s03_bracer_r",

	objectCRC = 3502532092,

	objectType = ARMARMOR,

	armorType = ARMOR_BRACERR,

	equipped = "0"
}

general_ithorian_male_items = {ichestplate, igloves, ileggings, ihelmet, ibracerr, ibracerl, ibicepl, ibicepr}

--------------------------Female Ithorian Items---------------------------

general_ithorian_female_items = {ichestplate, igloves, ileggings, ihelmet, ibracerr, ibracerl, ibicepl, ibicepr}

--------------------------Male Wookiee Items---------------------------

wookchest = {
	

	objectName = "Kasshyykian Hunting Armor Chestplate",

	templateName = "armor_kashyyykian_hunting_chest_plate",

	objectCRC = 3776759545,

	objectType = BODYARMOR,

	armorType = ARMOR_CHEST,

	equipped = "0"
}

wookleg = {
	

	objectName = "Kasshyykian Hunting Armor Leggings",

	templateName = "armor_kashyyykian_hunting_leggings",

	objectCRC = 4053289243,

	objectType = LEGARMOR,

	armorType = ARMOR_LEG,

	equipped = "0"
}

wookbracerl = {
	

	objectName = "Kasshyykian Hunting Armor Bracer",

	templateName = "armor_kashyyykian_hunting_bracer_l",

	objectCRC = 2126287876,

	objectType = ARMARMOR,

	armorType = ARMOR_BRACERL,

	equipped = "0"
}

wookbracerr = {
	

	objectName = "Kasshyykian Hunting Armor Bracer",

	templateName = "armor_kashyyykian_hunting_bracer_r",

	objectCRC = 241815959,

	objectType = ARMARMOR,

	armorType = ARMOR_BRACERR,

	equipped = "0"
}

bowcaster = {
	

	objectName = "Bowcaster",

	templateName = "object/weapon/ranged/rifle/shared_rifle_bowcaster.iff",

	objectCRC = 2976096139,

	objectType = RIFLE,

	damageType = WEAPON_ENERGY,

	armorPiercing = WEAPON_NONE,
	
	certification = "",

	equipped = "0"
}

general_wookie_male_items = {wookchest, wookleg, wookbracerl, wookbracerr, bowcaster}

--------------------------Female Wookie Items---------------------------

general_wookie_female_items = {wookchest, wookleg, wookbracerl, wookbracerr, bowcaster}

--------------------------General Items (All Species)---------------------------

maroj_melon = {
	

	objectName = "Maroj Melon",

	templateName = "object/tangible/food/foraged/shared_foraged_fruit_s1.iff",

	objectCRC = 1125771498,

	objectType = FOOD
}

g_baton = {
	

	objectName = "Gaderiffi Baton",

	templateName = "object/weapon/melee/baton/shared_baton_gaderiffi.iff",

	objectCRC = 1521219232,

	objectType = ONEHANDMELEEWEAPON,

	damageType = WEAPON_KINETIC,

	armorPiercing = WEAPON_NONE,
	
	certification = "cert_baton_gaderiffi",

	equipped = "0"
}

vk = {
	

	objectName = "Vibroknuckler",

	templateName = "object/weapon/melee/special/shared_vibroknuckler.iff",

	objectCRC = 1697024206,

	objectType = MELEEWEAPON,

	damageType = WEAPON_KINETIC,

	armorPiercing = WEAPON_LIGHT,
	
	certification = "cert_vibroknuckler",

	equipped = "0"
}

t21 = {
	

	objectName = "T21 Rifle",

	templateName = "object/weapon/ranged/rifle/shared_rifle_t21.iff",

	objectCRC = 1951509016,

	objectType = RIFLE,

	damageType = WEAPON_ENERGY,

	armorPiercing = WEAPON_HEAVY,
	
	certification = "cert_rifle_t21",

	equipped = "0"
}

viblance = {
	

	objectName = "Vibrolance",

	templateName = "object/weapon/melee/polearm/shared_lance_vibrolance.iff",

	objectCRC = 22784428,

	objectType = POLEARM,

	damageType = WEAPON_ELECTRICAL,

	armorPiercing = WEAPON_LIGHT,
	
	certification = "cert_lance_vibrolance",

	equipped = "0"
}

mst = {
	

	objectName = "Mineral Survey Tool",

	templateName = "survey_tool_mineral",

	objectCRC = 2862265132,

	objectType = SURVEYTOOL
}

sst = {
	

	objectName = "Solar Survey Tool",

	templateName = "survey_tool_solar",

	objectCRC = 2341848205,

	objectType = SURVEYTOOL
}


cst = {
	

	objectName = "Chemical Survey Tool",

	templateName = "survey_tool_chemical",

	objectCRC = 2242363434,

	objectType = SURVEYTOOL
}


fst = {
	

	objectName = "Flora Survey Tool",

	templateName = "survey_tool_flora",

	objectCRC = 1329114448,

	objectType = SURVEYTOOL
}


gst = {
	

	objectName = "Gas Survey Tool",

	templateName = "survey_tool_gas",

	objectCRC = 1059021891,

	objectType = SURVEYTOOL
}


watst = {
	

	objectName = "Water Survey Tool",

	templateName = "survey_tool_water",

	objectCRC = 2175673400,

	objectType = SURVEYTOOL
}


wndst = {
	

	objectName = "Wind Survey Tool",

	templateName = "survey_tool_wind",

	objectCRC = 566467536,

	objectType = SURVEYTOOL
}

fizz = {
	

	objectName = "a Fizz",

	templateName = "obj_fizz",

	objectCRC = 197364379,

	objectType = INSTRUMENT,

	instrumentType = INSTR_FIZZ,

	equipped = "0"
	
}

fanfar = {
	

	objectName = "a Fanfar",

	templateName = "obj_fanfar",

	objectCRC = 2024043623,

	objectType = INSTRUMENT,

	instrumentType = INSTR_FANFAR,

	equipped = "0"
}

kloohorn = {
	

	objectName = "a Kloohorn",

	templateName = "obj_kloo_horn",

	objectCRC = 4261135292,

	objectType = INSTRUMENT,

	instrumentType = INSTR_KLOOHORN,

	equipped = "0"
}

mand = {
	

	objectName = "a Mandoviol",

	templateName = "obj_mandoviol",

	objectCRC = 1784205003,

	objectType = INSTRUMENT,

	instrumentType = INSTR_MANDOVIOL,

	equipped = "0"
}

traz = {
	

	objectName = "a Traz",

	templateName = "obj_traz",

	objectCRC = 395515554,

	objectType = INSTRUMENT,

	instrumentType = INSTR_TRAZ,

	equipped = "0"
}

bandfill = {
	

	objectName = "a Bandfill",

	templateName = "obj_bandfill",

	objectCRC = 838757271,

	objectType = INSTRUMENT,

	instrumentType = INSTR_BANDFILL,

	equipped = "0"
}

flute = {
	

	objectName = "a Flutedroopy",

	templateName = "obj_flute_droopy",

	objectCRC = 1186559398,

	objectType = INSTRUMENT,

	instrumentType = INSTR_FLUTEDROOPY,

	equipped = "0"
}


general_general_items = {maroj_melon, g_baton, vk, t21, viblance,
			 mst, sst, cst, fst, gst, watst, wndst, fizz, 
			fanfar, kloohorn, mand, traz, bandfill, flute}

createItemsFromList("general", "humanoid", "male", general_humanoid_male_items)
createItemsFromList("general", "humanoid", "female", general_humanoid_female_items)
createItemsFromList("general", "trandoshan", "male", general_trandoshan_male_items)
createItemsFromList("general", "trandoshan", "female", general_trandoshan_female_items)
createItemsFromList("general", "ithorian", "male", general_ithorian_male_items)
createItemsFromList("general", "ithorian", "female", general_ithorian_female_items)
createItemsFromList("general", "wookiee", "male", general_wookie_male_items)
createItemsFromList("general", "wookiee", "female", general_wookie_female_items)
createItemsFromList("general", "all", "both", general_general_items)