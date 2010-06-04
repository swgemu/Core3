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

includeFile("cell/cell.lua")
includeFile("group/group_object.lua")
includeFile("player/player.lua")
includeFile("building/player/player_house_corellia.lua");
includeFile("building/player/player_house_generic.lua");
includeFile("building/player/player_house_naboo.lua");
includeFile("building/player/player_house_tatooine.lua");
includeFile("building/player/player_merchant_tent.lua");
includeFile("creature/player/bothan_female.lua")
includeFile("creature/player/bothan_male.lua")
includeFile("creature/player/human_female.lua")
includeFile("creature/player/human_male.lua")
includeFile("creature/player/ithorian_female.lua")
includeFile("creature/player/ithorian_male.lua")
includeFile("creature/player/moncal_female.lua")
includeFile("creature/player/moncal_male.lua")
includeFile("creature/player/rodian_female.lua")
includeFile("creature/player/rodian_male.lua")
includeFile("creature/player/sullustan_female.lua")
includeFile("creature/player/sullustan_male.lua")
includeFile("creature/player/trandoshan_female.lua")
includeFile("creature/player/trandoshan_male.lua")
includeFile("creature/player/twilek_female.lua")
includeFile("creature/player/twilek_male.lua")
includeFile("creature/player/wookiee_female.lua")
includeFile("creature/player/wookiee_male.lua")
includeFile("creature/player/zabrak_female.lua")
includeFile("creature/player/zabrak_male.lua")
includeFile("tangible/deed/guild_deed/guild_deeds.lua")
includeFile("tangible/deed/player_house_deed/corellia_house_deeds.lua")
includeFile("tangible/deed/player_house_deed/generic_house_deeds.lua")
includeFile("tangible/deed/player_house_deed/naboo_house_deeds.lua")
includeFile("tangible/deed/player_house_deed/tatooine_house_deeds.lua")
includeFile("tangible/newbie_tutorial/terminal_warp.lua")
includeFile("resource_container/resource_spawn.lua")
includeFile("resource_container/bottle_milk.lua")
includeFile("resource_container/bottle_water.lua")
includeFile("resource_container/energy_gas.lua")
includeFile("resource_container/energy_liquid.lua")
includeFile("resource_container/energy_radioactive.lua")
includeFile("resource_container/energy_solid.lua")
includeFile("resource_container/inorganic_chemicals.lua")
includeFile("resource_container/inorganic_gas.lua")
includeFile("resource_container/inorganic_minerals.lua")
includeFile("resource_container/inorganic_water.lua")
includeFile("resource_container/organic_bean.lua")
includeFile("resource_container/organic_bristley_hide.lua")
includeFile("resource_container/organic_corn.lua")
includeFile("resource_container/organic_food.lua")
includeFile("resource_container/organic_fruit.lua")
includeFile("resource_container/organic_fungi.lua")
includeFile("resource_container/organic_green_vegetables.lua")
includeFile("resource_container/organic_hide.lua")
includeFile("resource_container/organic_leathery_hide.lua")
includeFile("resource_container/organic_oats.lua")
includeFile("resource_container/organic_rice.lua")
includeFile("resource_container/organic_scaley_hide.lua")
includeFile("resource_container/organic_structure.lua")
includeFile("resource_container/organic_tuber.lua")
includeFile("resource_container/organic_wheat.lua")
includeFile("resource_container/organic_wooly_hide.lua")
includeFile("resource_container/inorganic_petrochem_liquid.lua")
includeFile("tangible/terminal/terminal_character_builder.lua")
includeFile("tangible/wearables/bodysuit/bodysuit_s13.lua")
includeFile("tangible/wearables/shoes/shoes_s01.lua")
includeFile("tangible/wearables/shoes/shoes_s02.lua")
includeFile("tangible/wearables/shoes/shoes_s07.lua")
includeFile("tangible/wearables/shoes/shoes_s09.lua")
includeFile("tangible/wearables/pants/pants_s29.lua")
includeFile("tangible/wearables/pants/pants_s14.lua")
includeFile("tangible/wearables/pants/pants_s04.lua")
includeFile("tangible/wearables/pants/pants_s07.lua")
includeFile("tangible/wearables/pants/pants_s08.lua")
includeFile("tangible/wearables/pants/pants_s11.lua")
includeFile("tangible/wearables/pants/pants_s12.lua")
includeFile("tangible/wearables/pants/pants_s21.lua")
includeFile("tangible/wearables/pants/pants_s24.lua")
includeFile("tangible/wearables/shirt/shirt_s34.lua")
includeFile("tangible/wearables/shirt/shirt_s12.lua")
includeFile("tangible/wearables/shirt/shirt_s10.lua")
includeFile("tangible/wearables/shirt/shirt_s14.lua")
includeFile("tangible/wearables/shirt/shirt_s16.lua")
includeFile("tangible/wearables/shirt/shirt_s24.lua")
includeFile("tangible/wearables/shirt/shirt_s26.lua")
includeFile("tangible/wearables/shirt/shirt_s27.lua")
includeFile("tangible/wearables/shirt/shirt_s42.lua")
includeFile("tangible/wearables/shirt/shirt_s38.lua")
includeFile("tangible/wearables/boots/boots_s04.lua")
includeFile("tangible/wearables/boots/boots_s05.lua")
includeFile("tangible/wearables/boots/boots_s21.lua")
includeFile("tangible/wearables/jacket/jacket_s16.lua")
includeFile("tangible/wearables/jacket/jacket_s05.lua")
includeFile("tangible/wearables/jacket/jacket_s24.lua")
includeFile("tangible/wearables/gloves/gloves_s03.lua")
includeFile("tangible/wearables/ithorian/ith_shirt_s01.lua")
includeFile("tangible/wearables/ithorian/ith_shirt_s02.lua")
includeFile("tangible/wearables/ithorian/ith_shirt_s03.lua")
includeFile("tangible/wearables/ithorian/ith_shirt_s04.lua")
includeFile("tangible/wearables/ithorian/ith_shirt_s05.lua")
includeFile("tangible/wearables/ithorian/ith_shirt_s09.lua")
includeFile("tangible/wearables/ithorian/ith_shirt_s10.lua")
includeFile("tangible/wearables/ithorian/ith_shirt_s12.lua")
includeFile("tangible/wearables/ithorian/ith_vest_s02.lua")
includeFile("tangible/wearables/ithorian/ith_jacket_s02.lua")
includeFile("tangible/wearables/ithorian/ith_jacket_s05.lua")
includeFile("tangible/wearables/ithorian/ith_pants_s06.lua")
includeFile("tangible/wearables/ithorian/ith_pants_s04.lua")
includeFile("tangible/wearables/ithorian/ith_pants_s05.lua")
includeFile("tangible/wearables/ithorian/ith_pants_s07.lua")
includeFile("tangible/wearables/ithorian/ith_pants_s08.lua")
includeFile("tangible/wearables/ithorian/ith_pants_s10.lua")
includeFile("tangible/wearables/ithorian/ith_pants_s12.lua")
includeFile("tangible/wearables/ithorian/ith_pants_s21.lua")
includeFile("tangible/wearables/ithorian/ith_gloves_s01.lua")
includeFile("tangible/wearables/skirt/skirt_s10.lua")
includeFile("weapon/creature/creature_default_weapon.lua")
includeFile("weapon/melee/knife/knife_survival.lua")
includeFile("weapon/melee/unarmed/unarmed_default_player.lua")
includeFile("weapon/ranged/pistol/pistol_cdef.lua")
includeFile("weapon/ranged/rifle/rifle_bowcaster.lua")
includeFile("tangible/crafting/station/generic_tool.lua")
includeFile("tangible/survey_tool/survey_tool_mineral.lua")
includeFile("tangible/survey_tool/survey_tool_liquid.lua")
includeFile("tangible/survey_tool/survey_tool_gas.lua")
includeFile("tangible/survey_tool/survey_tool_inorganic.lua")
includeFile("tangible/survey_tool/survey_tool_lumber.lua")
includeFile("tangible/survey_tool/survey_tool_moisture.lua")
includeFile("tangible/survey_tool/survey_tool_organic.lua")
includeFile("tangible/survey_tool/survey_tool_solar.lua")
includeFile("tangible/survey_tool/survey_tool_wind.lua")
includeFile("tangible/instrument/slitherhorn.lua")
includeFile("tangible/food/foraged/foraged_fruit_s1.lua")
includeFile("tangible/wearables/vest/vest_s09.lua")
includeFile("tangible/wearables/vest/vest_s10.lua")
includeFile("mobile/vehicle/speederbike_swoop.lua")
includeFile("mobile/dressed_merchant_trainer_01.lua")
includeFile("intangible/vehicle/speederbike_swoop_pcd.lua")
includeFile("tangible/fishing/fish/fish.lua")
includeFile("creature/npc/theme_park/player_shuttle.lua")
includeFile("creature/npc/theme_park/player_transport.lua")
includeFile("creature/npc/theme_park/player_transport_theed_hangar.lua")
includeFile("tangible/travel/ticket_collector/ticket_collector.lua")
includeFile("tangible/terminal/terminal_travel.lua")
includeFile("tangible/wearables/armor/composite/composite_set1.lua")
includeFile("badge_area.lua")







