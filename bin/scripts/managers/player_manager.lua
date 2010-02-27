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

object = {
	profession = "",
	species = "",
	sex = "",
	item = { }
}

function createItemsFromList(Profession, Species, Sex, List)
	for element in list_iter(List) do
		local ob = object
		ob.profession = Profession
		ob.species = Species
		ob.sex = Sex
		ob.item = element
		AddStartingItemToServer(ob)
	end
end

function list_iter (t)
      local i = 0
      local n = table.getn(t)
      return function ()
               i = i + 1
               if i <= n then return t[i] end
             end
end

dressShoes = {
	template = "object/tangible/wearables/shoes/shoes_s01.iff",
	equipped = 1
}

craftersPants = {
	template = "object/tangible/wearables/pants/pants_s29.iff",
	equipped = 1
}

softUndershirt = {
	template = "object/tangible/wearables/shirt/shirt_s34.iff",
	equipped = 1
}

cdefPistol = {
	template = "object/weapon/ranged/pistol/pistol_cdef.iff",
	equipped = 0
}

survivalKnife = {
	template = "object/weapon/melee/knife/knife_survival.iff",
	equipped = 0
}

generic_tool = {
	template = "object/tangible/crafting/station/generic_tool.iff",
	equipped = 0
}

mineral_tool = {
	template = "object/tangible/survey_tool/survey_tool_mineral.iff",
	equipped = 0
}

chemical_tool = {
	template = "object/tangible/survey_tool/survey_tool_liquid.iff",
	equipped = 0
}

sandals = {
	template = "object/tangible/wearables/shoes/shoes_s07.iff",
	equipped = 1
}

flaredCuffShirt = {
	template = "object/tangible/wearables/shirt/shirt_s12.iff",
	equipped = 1
}

wrappedSkirt = {
	template = "object/tangible/wearables/skirt/skirt_s10.iff",
	equipped = 1
}

ithMysticShirt = {
	template = "object/tangible/wearables/ithorian/ith_shirt_s10.iff",
	equipped = 1
}

ithPatrolPants = {
	template = "object/tangible/wearables/ithorian/ith_pants_s06.iff",
	equipped = 1
}

ithDressVest = {
	template = "object/tangible/wearables/ithorian/ith_vest_s02.iff",
	equipped = 1
}

ithStripedShirt = {
	template = "object/tangible/wearables/ithorian/ith_shirt_s05.iff",
	equipped = 1
}

---------------------Male Humanoid Items------------------------------------

artisan_humanoid_male_items = {dressShoes, craftersPants, softUndershirt}

--------------------------Female Humanoid Items---------------------------

artisan_humanoid_female_items = {sandals, flaredCuffShirt, wrappedSkirt}

--------------------------Male Trandoshan Items---------------------------

artisan_trandoshan_male_items = {craftersPants, softUndershirt}

--------------------------Female Trandoshan Items------------------------

artisan_trandoshan_female_items = {flaredCuffShirt, wrappedSkirt}

--------------------------Male Ithorian Items---------------------------

artisan_ithorian_male_items = {ithMysticShirt, ithPatrolPants, ithDressVest}

--------------------------Female Ithorian Items---------------------------

artisan_ithorian_female_items = {ithPatrolPants, ithStripedShirt, ithDressVest}

--------------------------Wookiee Items---------------------------

artisan_wookie_male_items = { }
artisan_wookie_female_items = { }

-------------------Artisan Items (All Species)--------------------

general_artisan_items = {cdefPistol, survivalKnife, generic_tool, mineral_tool, chemical_tool}


createItemsFromList("artisan", "humanoid", "male", artisan_humanoid_male_items)
createItemsFromList("artisan", "humanoid", "female", artisan_humanoid_female_items)
createItemsFromList("artisan", "trandoshan", "male", artisan_trandoshan_male_items)
createItemsFromList("artisan", "trandoshan", "female", artisan_trandoshan_female_items)
createItemsFromList("artisan", "ithorian", "male", artisan_ithorian_male_items)
createItemsFromList("artisan", "ithorian", "female", artisan_ithorian_female_items)
createItemsFromList("artisan", "wookiee", "male", artisan_wookie_male_items)
createItemsFromList("artisan", "wookiee", "female", artisan_wookie_female_items)
createItemsFromList("artisan", "all", "both", general_artisan_items)

sturdyBoots = {
	template = "object/tangible/wearables/boots/boots_s05.iff",
	equipped = 1
}

coldWeatherJacket = {
	template = "object/tangible/wearables/jacket/jacket_s16.iff",
	equipped = 1
}

formFittingUndershirt = {
	template = "object/tangible/wearables/shirt/shirt_s14.iff",
	equipped = 1
}

largePocketPants = {
	template = "object/tangible/wearables/pants/pants_s14.iff",
	equipped = 1
}

shortSleeveShirt = {
	template = "object/tangible/wearables/shirt/shirt_s27.iff",
	equipped = 1
}

basicCamos = {
	template = "object/tangible/wearables/pants/pants_s07.iff",
	equipped = 1
}

coldWeatherGloves = {
	template = "object/tangible/wearables/gloves/gloves_s03.iff",
	equipped = 1
}

ithReinforcedTrousers = {
	template = "object/tangible/wearables/ithorian/ith_pants_s04.iff",
	equipped = 1
}

ithFrillyShirt = {
	template = "object/tangible/wearables/ithorian/ith_shirt_s02.iff",
	equipped = 1
}

ithPaddedTrousers = {
	template = "object/tangible/wearables/ithorian/ith_pants_s07.iff",
	equipped = 1
}

ithBrawlingGloves = {
	template = "object/tangible/wearables/ithorian/ith_gloves_s01.iff",
	equipped = 1
}

---------------------Male Humanoid Items------------------------------------

brawler_humanoid_male_items = {sturdyBoots, coldWeatherJacket, formFittingUndershirt, largePocketPants}

--------------------------Female Humanoid Items---------------------------

brawler_humanoid_female_items = {sturdyBoots, shortSleeveShirt, basicCamos, coldWeatherGloves}


--------------------------Male Trandoshan Items---------------------------

brawler_trandoshan_male_items = {coldWeatherJacket, formFittingUndershirt, largePocketPants}

--------------------------Female Trandoshan Items------------------------

brawler_trandoshan_female_items = {shortsSleeveShirt, basicCamos, coldWeatherGloves}

--------------------------Male Ithorian Items---------------------------

brawler_ithorian_male_items = {ithReinforcedTrousers, ithFrillyShirt}

--------------------------Female Ithorian Items---------------------------

brawler_ithorian_female_items = {ithPaddedTrousers, ithFrillyShirt, ithBrawlingGloves}

brawler_wookie_male_items = { }
brawler_wookie_female_items = { }

-------------------Brawler Items (All Species)--------------------

general_brawler_items = {survivalKnife}

createItemsFromList("brawler", "humanoid", "male", brawler_humanoid_male_items)
createItemsFromList("brawler", "humanoid", "female", brawler_humanoid_female_items)
createItemsFromList("brawler", "trandoshan", "male", brawler_trandoshan_male_items)
createItemsFromList("brawler", "trandoshan", "female", brawler_trandoshan_female_items)
createItemsFromList("brawler", "ithorian", "male", brawler_ithorian_male_items)
createItemsFromList("brawler", "ithorian", "female", brawler_ithorian_female_items)
createItemsFromList("brawler", "wookiee", "male", brawler_wookie_male_items)
createItemsFromList("brawler", "wookiee", "female", brawler_wookie_female_items)
createItemsFromList("brawler", "all", "both", general_brawler_items)

stripedSlacks = {
	template = "object/tangible/wearables/pants/pants_s08.iff",
	equipped = 1
}

muscleShirt = {
	template = "object/tangible/wearables/shirt/shirt_s42.iff",
	equipped = 1
}

dressSlippers = {
	template = "object/tangible/wearables/shoes/shoes_s09.iff", 
	equipped = 1
}

flexFormShirt = {
	template = "object/tangible/wearables/shirt/shirt_s38.iff",
	equipped = 1
}

desertCrawlers = {
	template = "object/tangible/wearables/pants/pants_s11.iff",
	equipped = 1
}

ithKnittedShirt = {
	template = "object/tangible/wearables/ithorian/ith_shirt_s03.iff",
	equipped = 1
}

ithBaggies = {
	template = "object/tangible/wearables/ithorian/ith_pants_s08.iff",
	equipped = 1
}

ithBucklePants = {
	template = "object/tangible/wearables/ithorian/ith_pants_s10.iff",
	equipped = 1
}

ithFadeDyedShirt = {
	template = "object/tangible/wearables/ithorian/ith_shirt_s09.iff",
	equipped = 1
}

slitherhorn = {
	template = "object/tangible/instrument/slitherhorn.iff",
	equipped = 0
}

---------------------Male Humanoid Items------------------------------------

entertainer_humanoid_male_items = {dressShoes, stripedSlacks, muscleShirt}

--------------------------Female Humanoid Items---------------------------

entertainer_humanoid_female_items = {dressSlippers, flexFormShirt, desertCrawlers}

--------------------------Male Trandoshan Items---------------------------

entertainer_trandoshan_male_items = {stripedSlacks, muscleShirt}

--------------------------Female Trandoshan Items------------------------

entertainer_trandoshan_female_items = {flexFormShirt, desertCrawlers}

--------------------------Male Ithorian Items---------------------------

entertainer_ithorian_male_items = {ithKnittedShirt, ithBaggies}

--------------------------Female Ithorian Items---------------------------

entertainer_ithorian_female_items = {ithBucklePants, ithFadeDyedShirt}

entertainer_wookie_male_items = { }
entertainer_wookie_female_items = { }

-------------------Entertainer Items (All Species)--------------------


general_entertainer_items = {cdefPistol, survivalKnife, slitherhorn}

createItemsFromList("entertainer", "humanoid", "male", entertainer_humanoid_male_items)
createItemsFromList("entertainer", "humanoid", "female", entertainer_humanoid_female_items)
createItemsFromList("entertainer", "trandoshan", "male", entertainer_trandoshan_male_items)
createItemsFromList("entertainer", "trandoshan", "female", entertainer_trandoshan_female_items)
createItemsFromList("entertainer", "ithorian", "male", entertainer_ithorian_male_items)
createItemsFromList("entertainer", "ithorian", "female", entertainer_ithorian_female_items)
createItemsFromList("entertainer", "wookiee", "male", entertainer_wookie_male_items)
createItemsFromList("entertainer", "wookiee", "female", entertainer_wookie_female_items)
createItemsFromList("entertainer", "all", "both", general_entertainer_items)


bowcaster = {
	template = "object/weapon/ranged/rifle/rifle_bowcaster.iff",
	equipped = 0
}

maroj_melon = {
	template = "object/tangible/food/foraged/foraged_fruit_s1.iff",
	equipped = 0
}

---------------------Male Humanoid Items------------------------------------

general_humanoid_male_items = { }

--------------------------Female Humanoid Items---------------------------

general_humanoid_female_items = { }

----------------------------Male Trandoshan Items---------------------------

general_trandoshan_male_items = { }

--------------------------Female Trandoshan Items---------------------------

general_trandoshan_female_items = { }

--------------------------Male Ithorian Items---------------------------

general_ithorian_male_items = { }

--------------------------Female Ithorian Items---------------------------

general_ithorian_female_items = { }

--------------------------Male Wookiee Items---------------------------

general_wookie_male_items = { bowcaster}

--------------------------Female Wookie Items---------------------------

general_wookie_female_items = { bowcaster}

--------------------------General Items (All Species)---------------------------

general_general_items = {maroj_melon}

createItemsFromList("general", "humanoid", "male", general_humanoid_male_items)
createItemsFromList("general", "humanoid", "female", general_humanoid_female_items)
createItemsFromList("general", "trandoshan", "male", general_trandoshan_male_items)
createItemsFromList("general", "trandoshan", "female", general_trandoshan_female_items)
createItemsFromList("general", "ithorian", "male", general_ithorian_male_items)
createItemsFromList("general", "ithorian", "female", general_ithorian_female_items)
createItemsFromList("general", "wookiee", "male", general_wookie_male_items)
createItemsFromList("general", "wookiee", "female", general_wookie_female_items)
createItemsFromList("general", "all", "both", general_general_items)

