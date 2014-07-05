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

-----------------------------------
--GENERAL PLAYER SETTINGS
-----------------------------------

--Blue frog / GM buff values
performanceBuff = 1000
medicalBuff = 1900
performanceDuration = 7200 -- in seconds
medicalDuration = 7200 -- in seconds

--Sets the experience multiplier while grouped
groupExpMultiplier = 1.2

--Sets a global experience multiplier
globalExpMultiplier = 1.0

--Sets the base number of control devices of each type that a player can have in their datapad at once
--For creature pets, A Creature Handler will have the base number + their stored pets skill mod as limit
baseStoredCreaturePets = 2
baseStoredFactionPets = 3
baseStoredDroids = 5
baseStoredVehicles = 3
baseStoredShips = 3

-----------------------------------
--VETERAN REWARDS CONFIG
-----------------------------------
-- TODO: CHANGE TO {90, 180, 270, 360, 450, 540, 630, 720, 810, 900, 990, 1080} AFTER TESTING
veteranRewardMilestones = {3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36} --days, must be sorted low to high

veteranRewards = {

	-- 90 Day Rewards
	-- TODO: CHANGE TO 90 AFTER TESTING
	-- Disabled until harvester is functional {templateFile = "object/tangible/veteran_reward/harvester.iff", milestone=90, oneTime=true, description="@veteran_new:poweredharvester"},
	{templateFile = "object/tangible/veteran_reward/data_terminal_s1.iff", milestone=3, oneTime=false, description="@veteran_new:dataterminal1"},
	{templateFile = "object/tangible/veteran_reward/data_terminal_s2.iff", milestone=3, oneTime=false, description="@veteran_new:dataterminal2"},
	{templateFile = "object/tangible/veteran_reward/data_terminal_s3.iff", milestone=3, oneTime=false, description="@veteran_new:dataterminal3"},
	{templateFile = "object/tangible/veteran_reward/data_terminal_s4.iff", milestone=3, oneTime=false, description="@veteran_new:dataterminal4"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_protocol_droid_toy.iff", milestone=3, oneTime=false, description="@veteran_new:mini_protocoldroid"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_r2_toy.iff", milestone=3, oneTime=false, description="@veteran_new:mini_r2"},

	-- 180 Day Rewards
	-- TODO: CHANGE TO 180 AFTER TESTING
	{templateFile = "object/tangible/veteran_reward/resource.iff", milestone=6, oneTime=true, description="@veteran_new:resourcecrate"},
	{templateFile = "object/tangible/veteran_reward/frn_couch_falcon_corner_s01.iff", milestone=6, oneTime=false, description="@veteran_new:falconcouch"},
	{templateFile = "object/tangible/veteran_reward/frn_couch_falcon_section_s01.iff", milestone=6, oneTime=false, description="@veteran_new:falconchair"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_tie_fighter_toy.iff", milestone=6, oneTime=false, description="@veteran_new:mini_tiefighter"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_x_wing_toy.iff", milestone=6, oneTime=false, description="@veteran_new:mini_xwing"},

	-- 270 Day Rewards
	-- TODO: CHANGE TO 270 AFTER TESTING
	{templateFile = "object/tangible/deed/vehicle_deed/speederbike_flash_deed.iff", milestone=9, oneTime=false},
	{templateFile = "object/tangible/wearables/goggles/goggles_s01.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 1"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s02.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 2"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s03.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 3"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s04.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 4"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s05.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 5"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s06.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 6"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_darth_vader_toy.iff", milestone=9, oneTime=false, description="@veteran_new:mini_darthvader"},

	-- 360 Day Rewards
	-- TODO: CHANGE TO 360 AFTER TESTING
	{templateFile = "object/tangible/veteran_reward/frn_tech_console_sectional_a.iff", milestone=12, oneTime=false, description="@veteran_new:techconsole_a"},
	{templateFile = "object/tangible/veteran_reward/frn_tech_console_sectional_b.iff", milestone=12, oneTime=false, description="@veteran_new:techconsole_b"},
	{templateFile = "object/tangible/veteran_reward/frn_tech_console_sectional_c.iff", milestone=12, oneTime=false, description="@veteran_new:techconsole_c"},
	{templateFile = "object/tangible/veteran_reward/frn_tech_console_sectional_d.iff", milestone=12, oneTime=false, description="@veteran_new:techconsole_d"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_jabba_toy.iff", milestone=12, oneTime=false, description="@veteran_new:mini_jabba"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_stormtrooper_toy.iff", milestone=12, oneTime=false, description="@veteran_new:mini_stormtrooper"},
	--Disabled until kits are functional {templateFile = "object/tangible/veteran_reward/antidecay.iff", milestone=12, oneTime=true, description="@veteran_new:antidecay"},
	
	-- 450 Day Rewards
	-- TODO: CHANGE TO 450 AFTER TESTING
	{templateFile = "object/tangible/camp/camp_spit_s2.iff", milestone=15, oneTime=false, description="Camp Center (Small)"},
	{templateFile = "object/tangible/camp/camp_spit_s3.iff", milestone=15, oneTime=false, description="Camp Center (Large)"},
	{templateFile = "object/tangible/furniture/tatooine/frn_tato_meat_rack.iff", milestone=15, oneTime=false, description="@frn_n:frn_tato_meat_rack"},
	{templateFile = "object/tangible/furniture/tatooine/frn_tato_vase_style_01.iff", milestone=15, oneTime=false, description="Gold Ornamental Vase (Style 1)"},
	{templateFile = "object/tangible/furniture/tatooine/frn_tato_vase_style_02.iff", milestone=15, oneTime=false, description="Gold Ornamental Vase (Style 2)"},
	{templateFile = "object/tangible/furniture/decorative/foodcart.iff", milestone=15, oneTime=false, description="Foodcart"},
	{templateFile = "object/tangible/furniture/all/frn_bench_generic.iff", milestone=15, oneTime=false, description="Park Bench"},
	
	-- 540 Day Rewards
	-- TODO: CHANGE TO 540 AFTER TESTING
	{templateFile = "object/tangible/painting/painting_wookiee_m.iff", milestone=18, oneTime=false, description="@frn_n:painting_wookiee_m"},
	{templateFile = "object/tangible/painting/painting_wookiee_f.iff", milestone=18, oneTime=false, description="@frn_n:painting_wookiee_f"},
	{templateFile = "object/tangible/painting/painting_trees_s01.iff", milestone=18, oneTime=false, description="@frn_n:painting_trees_s01"},
	{templateFile = "object/tangible/loot/quest/lifeday_orb.iff", milestone=18, oneTime=false, description="Lifeday Orb"},
		
	-- 630 Day Rewards
	-- TODO: CHANGE TO 630 AFTER TESTING
	{templateFile = "object/tangible/furniture/modern/bar_counter_s1.iff", milestone=21, oneTime=false, description="Bar Countertop"},
	{templateFile = "object/tangible/furniture/modern/bar_piece_curve_s1.iff", milestone=21, oneTime=false, description="Bar Countertop (Curved, Style 1)"},
	{templateFile = "object/tangible/furniture/modern/bar_piece_curve_s2.iff", milestone=21, oneTime=false, description="Bar Countertop (Curved, Style 2)"},
	{templateFile = "object/tangible/furniture/modern/bar_piece_straight_s1.iff", milestone=21, oneTime=false, description="Bar Countertop (Straight, Style 1)"},
	{templateFile = "object/tangible/furniture/modern/bar_piece_straight_s2.iff", milestone=21, oneTime=false, description="Bar Countertop (Straight, Style 2)"},
			
	-- 720 Day Rewards
	-- TODO: CHANGE TO 720 AFTER TESTING
	{templateFile = "object/tangible/furniture/all/frn_all_table_s01.iff", milestone=24, oneTime=false, description="Round Cantina Table (Style 1)"},
	{templateFile = "object/tangible/furniture/all/frn_all_table_s02.iff", milestone=24, oneTime=false, description="Round Cantina Table (Style 2)"},
	{templateFile = "object/tangible/furniture/all/frn_all_table_s03.iff", milestone=24, oneTime=false, description="Round Cantina Table (Style 3)"},
	{templateFile = "object/tangible/furniture/tatooine/frn_tatt_chair_cantina_seat_2.iff", milestone=24, oneTime=false, description="Large Cantina Sofa"},
	{templateFile = "object/tangible/furniture/tatooine/frn_tato_cafe_parasol.iff", milestone=24, oneTime=false, description="@frn_n:frn_tato_cafe_parasol"},
	{templateFile = "object/tangible/furniture/decorative/diagnostic_screen.iff", milestone=24, oneTime=false, description="@frn_n:diagnostic_screen"},
		
	-- 810 Day Rewards
	-- TODO: CHANGE TO 810 AFTER TESTING
	{templateFile = "object/tangible/furniture/all/frn_all_desk_map_table.iff", milestone=27, oneTime=false, description="Round Data Terminal"},
	{templateFile = "object/tangible/furniture/decorative/professor_desk.iff", milestone=27, oneTime=false, description="Professor Desk"},
	{templateFile = "object/tangible/furniture/modern/rug_oval_m_s02.iff", milestone=27, oneTime=false, description="Medium Oval Rug"},
	{templateFile = "object/tangible/furniture/modern/rug_oval_sml_s01.iff", milestone=27, oneTime=false, description="Small Oval Rug"},
	{templateFile = "object/tangible/furniture/modern/rug_rect_m_s01.iff", milestone=27, oneTime=false, description="Medium Rectangular Rug"},
	{templateFile = "object/tangible/furniture/modern/rug_rect_sml_s01.iff", milestone=27, oneTime=false, description="Small Rectangular Rug"},
	{templateFile = "object/tangible/furniture/modern/rug_rnd_m_s01.iff", milestone=27, oneTime=false, description="Medium Round Rug"},
	{templateFile = "object/tangible/furniture/modern/rug_rnd_sml_s01.iff", milestone=27, oneTime=false, description="Small Round Rug"},
	
	-- 900 Day Rewards
	-- TODO: CHANGE TO 900 AFTER TESTING
	{templateFile = "object/tangible/loot/misc/loot_skull_bith.iff", milestone=30, oneTime=false, description="A Bith Skull"},
	{templateFile = "object/tangible/loot/misc/loot_skull_human.iff", milestone=30, oneTime=false, description="A Human Skull"},
	{templateFile = "object/tangible/loot/misc/loot_skull_ithorian.iff", milestone=30, oneTime=false, description="A Ithorian Skull"},
	{templateFile = "object/tangible/loot/misc/loot_skull_thune.iff", milestone=30, oneTime=false, description="A Thune Skull"},
	{templateFile = "object/tangible/loot/misc/loot_skull_voritor.iff", milestone=30, oneTime=false, description="A Voritor Lizard Skull"},
	{templateFile = "object/tangible/furniture/all/event_flag_game_imp_banner.iff", milestone=30, oneTime=false, description="Imperial Banner"},
	{templateFile = "object/tangible/furniture/all/event_flag_game_neut_banner.iff", milestone=30, oneTime=false, description="Neutral Banner"},
	{templateFile = "object/tangible/furniture/all/event_flag_game_reb_banner.iff", milestone=30, oneTime=false, description="Rebel Banner"},
		
	-- 990 Day Rewards
	-- TODO: CHANGE TO 990 AFTER TESTING
	{templateFile = "object/tangible/furniture/modern/rug_oval_lg_s01.iff", milestone=33, oneTime=false, description="Large Rectangular Rug (Style 1)"},
	{templateFile = "object/tangible/furniture/modern/rug_rect_lg_s02.iff", milestone=33, oneTime=false, description="Large Rectangular Rug (Style 2)"},
	{templateFile = "object/tangible/furniture/modern/rug_oval_lg_s01.iff", milestone=33, oneTime=false, description="Large Oval Rug"},
	{templateFile = "object/tangible/furniture/modern/rug_rnd_lg_s01.iff", milestone=33, oneTime=false, description="Large Round Rug"},
	{templateFile = "object/tangible/furniture/all/frn_all_plant_potted_lg_s2.iff", milestone=33, oneTime=false, description="Large Potted Plant (Style 2)"},
	{templateFile = "object/tangible/furniture/all/frn_all_plant_potted_lg_s3.iff", milestone=33, oneTime=false, description="Large Potted Plant (Style 3)"},
	{templateFile = "object/tangible/furniture/all/frn_all_plant_potted_lg_s4.iff", milestone=33, oneTime=false, description="Large Potted Plant (Style 4)"},
		
	-- 1080 Day Rewards
	-- TODO: CHANGE TO 1080 AFTER TESTING	
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_01.iff", milestone=36, oneTime=false, description="Painting: Cast Wing in Flight"},
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_02.iff", milestone=36, oneTime=false, description="Painting: Decimator"},
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_03.iff", milestone=36, oneTime=false, description="Painting: Tatooine Dune Speeder"},
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_04.iff", milestone=36, oneTime=false, description="Painting: Weapon of War"},
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_05.iff", milestone=36, oneTime=false, description="Painting: Fighter Study"},
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_06.iff", milestone=36, oneTime=false, description="Painting: Hutt Greed"},
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_07.iff", milestone=36, oneTime=false, description="Painting: Smuggler's Run"},
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_08.iff", milestone=36, oneTime=false, description="Painting: Imperial Oppression (TIE Oppressor)"},
	{templateFile = "object/tangible/veteran_reward/one_year_anniversary/painting_09.iff", milestone=36, oneTime=false, description="Painting: Emperor's Eyes (TIE Sentinel)"},

}