--Copyright (C) 2010 <SWGEmu>


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
--
--NOTES ABOUT CHARACTER BUILDER TERMINAL ITEM LIST FORMAT
---------------------------------------------------------
--The item list is an infinitely deep node tree system.
--To create a sub menu, use the following format:
--"Name of the sub menu", {Menu items contained in brackets}
--To create an item that is selectable, use the following format (within brackets of a submenu):
--"Name of the item", "Path to the server or client template."
--Be sure to pay attention to commas.

object_tangible_terminal_terminal_character_builder = object_tangible_terminal_shared_terminal_character_builder:new {
	gameObjectType = 16400,
			
	maxCondition = 0,
	
	templateType = CHARACTERBUILDERTERMINAL,

	itemList = {
		"Armor",
		{
			"Composite Armor",
			{
				"Composite Left Bicep", "object/tangible/wearables/armor/composite/composite_set1_bicep_l.iff",
				"Composite Right Bicep", "object/tangible/wearables/armor/composite/composite_set1_bicep_r.iff",
				"Composite Boots", "object/tangible/wearables/armor/composite/composite_set1_boots.iff",
				"Composite Left Bracer", "object/tangible/wearables/armor/composite/composite_set1_bracer_l.iff",
				"Composite Right Bracer", "object/tangible/wearables/armor/composite/composite_set1_bracer_r.iff",
				"Composite Chest Plate", "object/tangible/wearables/armor/composite/composite_set1_chest_plate.iff",
				"Composite Gloves", "object/tangible/wearables/armor/composite/composite_set1_gloves.iff",
				"Composite Helmet", "object/tangible/wearables/armor/composite/composite_set1_helmet.iff",
				"Composite Leggings", "object/tangible/wearables/armor/composite/composite_set1_leggings.iff"
			}
		},
		"Clothes",
		{
			"Jedi Robes",
			{
					"Light Jedi Robes",
					{
					"Light Jedi Robe 1", "object/tangible/wearables/robe/robe_jedi_light_s01.iff",
					"Light Jedi Robe 2", "object/tangible/wearables/robe/robe_jedi_light_s02.iff",
					"Light Jedi Robe 3", "object/tangible/wearables/robe/robe_jedi_light_s03.iff",
					"Light Jedi Robe 4", "object/tangible/wearables/robe/robe_jedi_light_s04.iff",
					"Light Jedi Robe 5", "object/tangible/wearables/robe/robe_jedi_light_s05.iff"
					},
					
					"Dark Jedi Robes",
					{
					"Dark Jedi Robe 1", "object/tangible/wearables/robe/robe_jedi_dark_s01.iff",
					"Dark Jedi Robe 2", "object/tangible/wearables/robe/robe_jedi_dark_s02.iff",
					"Dark Jedi Robe 3", "object/tangible/wearables/robe/robe_jedi_dark_s03.iff",
					"Dark Jedi Robe 4", "object/tangible/wearables/robe/robe_jedi_dark_s04.iff",
					"Dark Jedi Robe 5", "object/tangible/wearables/robe/robe_jedi_dark_s05.iff"
					}
			}
		},
		"Furniture",
		{	
			"Paintings",
			{
				"Bestine Painting 1", "object/tangible/painting/bestine_history_quest_painting.iff",
				"Bestine Painting 2", "object/tangible/painting/bestine_quest_painting.iff",
				"Agrilat Swamp", "object/tangible/painting/painting_agrilat_s01.iff",
				"Armor Blueprints", "object/tangible/painting/painting_armor_blueprint.iff",
				"Blue Leaf Temple", "object/tangible/painting/painting_bestine_blueleaf_temple.iff",
				"Blumbush", "object/tangible/painting/painting_bestine_blumbush.iff",
				"Boffa Plant", "object/tangible/painting/painting_bestine_boffa.iff",
				"Abstract Painting of Golden Petals No. 1", "object/tangible/painting/painting_bestine_golden_flower_01.iff",
				"Abstract Painting of Golden Petals No. 2", "object/tangible/painting/painting_bestine_golden_flower_02.iff",
				"Abstract Painting of Golden Petals No. 3", "object/tangible/painting/painting_bestine_golden_flower_03.iff",
				"Krayt Dragon Skeleton", "object/tangible/painting/painting_bestine_krayt_skeleton.iff",
				"Lucky Despot", "object/tangible/painting/painting_bestine_lucky_despot.iff",
				"Mattberry Plant", "object/tangible/painting/painting_bestine_mattberry.iff",
				"Close-up of Mon Calamari Eye 1", "object/tangible/painting/painting_bestine_moncal_eye_01.iff",
				"Close-up of Mon Calamari Eye 2", "object/tangible/painting/painting_bestine_moncal_eye_02.iff",
				"Rainbow Berry Bush", "object/tangible/painting/painting_bestine_rainbow_berry_bush.iff",
				"Raventhorn", "object/tangible/painting/painting_bestine_raventhorn.iff",
				"Ronka", "object/tangible/painting/painting_bestine_ronka.iff",
				"Bothan (female)", "object/tangible/painting/painting_bothan_f.iff",
				"Bothan (male)", "object/tangible/painting/painting_bothan_m.iff",
				"Theed Waterfall", "object/tangible/painting/painting_waterfall.iff",
				"Stormtrooper", "object/tangible/painting/painting_bw_stormtrooper.iff",				
				"Han Solo Wanted", "object/tangible/painting/painting_han_wanted.iff",
				"Luke Skywalker Wanted", "object/tangible/painting/painting_luke_wanted.iff",
				"Princess Leia Wanted", "object/tangible/painting/painting_leia_wanted.iff",
				"Schematic (Droid)", "object/tangible/painting/painting_schematic_droid.iff",
				"Schematic (Transport Ship)", "object/tangible/painting/painting_schematic_transport_ship.iff",
				"Schematic (Weapon)", "object/tangible/painting/painting_schematic_weapon.iff",
				"Veteran Reward (Cast Wing in Flight)", "object/tangible/veteran_reward/one_year_anniversary/painting_01.iff",
				"Veteran Reward (Decimator)", "object/tangible/veteran_reward/one_year_anniversary/painting_02.iff",
				"Veteran Reward (Weapon of War)", "object/tangible/veteran_reward/one_year_anniversary/painting_03.iff",
				"Veteran Reward (Tatooine Dune Speeder)", "object/tangible/veteran_reward/one_year_anniversary/painting_04.iff",
				"Veteran Reward (Fighter Study)", "object/tangible/veteran_reward/one_year_anniversary/painting_05.iff",
				"Veteran Reward (Hutt Greed)", "object/tangible/veteran_reward/one_year_anniversary/painting_06.iff",
				"Veteran Reward (Smuggler's Run)", "object/tangible/veteran_reward/one_year_anniversary/painting_07.iff",
				"Veteran Reward (Imperial TIE Oppressor)", "object/tangible/veteran_reward/one_year_anniversary/painting_08.iff",
				"Veteran Reward (Emperor's Eyes TIE Sentinel)", "object/tangible/veteran_reward/one_year_anniversary/painting_09.iff"
			},
			"Veteran Rewards",
			{
				"YT-1300 Couch Corner", "object/tangible/veteran_reward/frn_couch_falcon_corner_s01.iff",
				"YT-1300 Couch Section", "object/tangible/veteran_reward/frn_couch_falcon_section_s01.iff",
				"Darth Vader Toy", "object/tangible/veteran_reward/frn_vet_darth_vader_toy.iff",
				"Jabba the Hutt Toy", "object/tangible/veteran_reward/frn_vet_jabba_toy.iff",
				"Protocol Droid Toy", "object/tangible/veteran_reward/frn_vet_protocol_droid_toy.iff",
				"R2 Droid Toy", "object/tangible/veteran_reward/frn_vet_r2_toy.iff",
				"Stormtrooper Toy", "object/tangible/veteran_reward/frn_vet_stormtrooper_toy.iff",
				"TIE Fighter Toy", "object/tangible/veteran_reward/frn_vet_tie_fighter_toy.iff",
				"X-Wing Toy", "object/tangible/veteran_reward/frn_vet_x_wing_toy.iff"				
			},
			"Lighting",
			{
				"Candle (Style 1)", "object/tangible/furniture/all/frn_all_lamp_candlestick_free_s01_lit.iff",
				"Candle (Style 2)", "object/tangible/furniture/all/frn_all_lamp_candlestick_free_s02_lit.iff",
				"Candle (Style 3)", "object/tangible/furniture/all/frn_all_lamp_candlestick_tbl_s01.iff",
				"Candle (Style 4)", "object/tangible/furniture/all/frn_all_lamp_candlestick_tbl_s02.iff",
				"Candle (Style 5)", "object/tangible/furniture/all/frn_all_lamp_candlestick_tbl_s03.iff",
				"Desk Lamp (Style 1)", "object/tangible/furniture/all/frn_all_lamp_desk_s01_lit.iff",
				"Desk Lamp (Style 2)", "object/tangible/furniture/all/frn_all_lamp_desk_s01_lit.iff",
				"Freestannding Lamp", "object/tangible/furniture/all/frn_all_lamp_free_s01.iff",
				"Free-Standing Lamp (Style 2", "object/tangible/furniture/all/frn_all_lamp_free_s02.iff"
			},				
			"Rugs",
			{
				"Large Rectangular Rug (Style 1)", "object/tangible/furniture/modern/rug_rect_lg_s01.iff",
				"Large Rectangular Rug (Style 2)", "object/tangible/furniture/modern/rug_rect_lg_s02.iff",
				"Large Round Rug (Style 1)", "object/tangible/furniture/modern/rug_rnd_lg_s01.iff",
				"Large Round Rug (Style 2)", "object/tangible/furniture/modern/rug_rnd_sml_s01.iff",
				"Large Oval Rug (Style 1)", "object/tangible/furniture/modern/rug_oval_sml_s01.iff",
				"Large Oval Rug (Style 2)", "object/tangible/furniture/modern/rug_oval_m_s02.iff",
				"Large Square Rug", "object/tangible/furniture/modern/rug_sqr_m_s01.iff",
				"Ornate Blue Rug", "object/tangible/loot/collectible/collectible_rewards/blue_rug.iff",
				"Ornate Orange Rug", "object/tangible/loot/collectible/collectible_rewards/orange_rug.iff"
			},
			"Plants",
			{
				"Large Potted Plant (Style 1)", "object/tangible/furniture/all/frn_all_plant_potted_lg_s1.iff",
				"Large Potted Plant (Style 2)", "object/tangible/furniture/all/frn_all_plant_potted_lg_s2.iff",
				"Large Potted Plant (Style 3)", "object/tangible/furniture/all/frn_all_plant_potted_lg_s3.iff",
				"Large Potted Plant (Style 4)", "object/tangible/furniture/all/frn_all_plant_potted_lg_s4.iff",
				"Small Potted Plant (Style 1)", "object/tangible/furniture/all/frn_all_potted_plants_sml_s01.ifff",
				"Small Potted Plant (Style 2)", "object/tangible/furniture/all/frn_all_potted_plants_sml_s02.ifff",
				"Small Potted Plant (Style 3)", "object/tangible/furniture/all/frn_all_potted_plants_sml_s03.ifff",
				"Small Potted Plant (Style 4)", "object/tangible/furniture/all/frn_all_potted_plants_sml_s04.ifff",
				"Potted Tree (Style 1)", "object/tangible/furniture/all/frn_all_tree_potted_s1.iff",
				"Potted Tree (Style 2)", "object/tangible/furniture/all/frn_all_tree_potted_s2.iff",
				"Fountain", "object/tangible/furniture/city/fountain_heroic.iff",
				"Brazier", "object/tangible/furniture/city/fountain_brazier_round.iff"
			},
			"Miscellaneous Decorations",
			{
				"Bacta Tank", "object/tangible/furniture/decorative/bacta_tank.iff",
				"Bottle (Style 1)", "object/tangible/furniture/decorative/bottle_pear.iff",
				"Bottle (Style 2)", "object/tangible/furniture/decorative/bottle_fat.iff",
				"Bottle (Style 3)", "object/tangible/furniture/decorative/bottle_tall.iff",
				"Bowl", "object/tangible/furniture/decorative/carved_bowl.iff",
				"Diagnostic Screen", "object/tangible/furniture/decorative/diagnostic_screen.iff",
				"Microphone", "object/tangible/furniture/decorative/microphone_s01.iff",
				"Radio", "object/tangible/furniture/decorative/radio.iff",
				"Imperial Banner", "object/tangible/furniture/all/bestine_quest_imp_banner.iff",
				"Rebel Banner", "object/tangible/furniture/all/frn_all_banner_rebel.iff",
				"Tiki Torch", "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff",
				"Stuffed Fish", "object/tangible/furniture/decorative/stuffed_fish.iff",
				"Blowfish", "object/tangible/fishing/fish/blowfish.iff",
				"Nabooian Sculpture", "object/tangible/loot/collectible/collectible_rewards/collectible_sculpture_s01.iff",
				"Glass Table", "object/tangible/loot/collectible/collectible_rewards/collectible_table.iff",
				"Bed", "object/tangible/furniture/all/frn_all_bed_lg_s1.iff"
			},			
			"Elegant Furniture",
			{
				"Elegant Armoire", "object/tangible/furniture/elegant/armoire_elegant_s01.iff",
				"Elegant Bookcase", "object/tangible/furniture/elegant/bookcase_s01.iff",
				"Elegant Cabinet", "object/tangible/furniture/elegant/cabinet_s01.iff",
				"Elegant Chair", "object/tangible/furniture/elegant/chair_s01.iff",
				"Elegant Chest", "object/tangible/furniture/elegant/chest_s01.iff",
				"Elegant Coffee Table", "object/tangible/furniture/elegant/coffee_table_s01.iff",
				"Elegant Couch", "object/tangible/furniture/elegant/couch_s01.iff",
				"Elegant End Table", "object/tangible/furniture/elegant/end_table_s01.iff",
				"Elegant Love Seat", "object/tangible/furniture/elegant/love_seat_s01.iff"
			},
			"Cheap Furniture",
			{
				"Cheap Armoire", "object/tangible/furniture/cheap/armoire_s01.iff",
				"Cheap Bookcase", "object/tangible/furniture/cheap/bookcase_s01.iff",
				"Cheap Cabinet", "object/tangible/furniture/cheap/cabinet_s01.iff",
				"Cheap Chair", "object/tangible/furniture/cheap/chair_s01.iff",
				"Cheap Chest", "object/tangible/furniture/cheap/chest_s01.iff",
				"Cheap Coffee Table", "object/tangible/furniture/cheap/coffee_table_s01.iff",
				"Cheap Couch", "object/tangible/furniture/cheap/couch_s01.iff",
				"Cheap End Table", "object/tangible/furniture/cheap/end_table_s01.iff",
				"Cheap Love Seat", "object/tangible/furniture/cheap/love_seat_s01.iff"
			},
			"Technical Furniture",
			{
				"Technical Armoire", "object/tangible/furniture/technical/armoire_s01.iff",
				"Technical Bookcase", "object/tangible/furniture/technical/bookcase_s01.iff",
				"Technical Cabinet", "object/tangible/furniture/technical/cabinet_s01.iff",
				"Technical Chair", "object/tangible/furniture/technical/chair_s01.iff",
				"Technical Chest", "object/tangible/furniture/technical/chest_s01.iff",
				"Technical Coffee Table", "object/tangible/furniture/technical/coffee_table_s01.iff",
				"Technical Couch", "object/tangible/furniture/technical/couch_s01.iff",
				"Technical End Table", "object/tangible/furniture/technical/end_table_s01.iff"
			},
			"Plain Furniture",
			{
				"Plain Armoire", "object/tangible/furniture/plain/plain_armoire_s01.iff",
				"Plain Bookcase", "object/tangible/furniture/plain/plain_bookcase_s01.iff",
				"Plain Cabinet", "object/tangible/furniture/plain/plain_cabinet_s01.iff",
				"Plain Chair", "object/tangible/furniture/plain/plain_chair_s01.iff",
				"Plain Chest", "object/tangible/furniture/plain/plain_chest_s01.iff",
				"Plain Coffee Table", "object/tangible/furniture/plain/plain_coffee_table_s01.iff",
				"Plain Couch", "object/tangible/furniture/plain/plain_couch_s01.iff",
				"Plain End Table", "object/tangible/furniture/plain/plain_end_table_s01.iff",
				"Plain Love Seat", "object/tangible/furniture/plain/plain_love_seat_s01.iff"
			},

			"Modern Furniture",
			{
				"Modern Armoire", "object/tangible/furniture/modern/armoire_modern_style_01.iff",
				"Modern Bookcase", "object/tangible/furniture/modern/bookcase_modern_style_01.iff",
				"Modern Cabinet", "object/tangible/furniture/modern/cabinet_modern_style_01.iff",
				"Modern Chair", "object/tangible/furniture/modern/chair_modern_style_01.iff",
				"Modern Chest", "object/tangible/furniture/modern/chest_modern_style_01.iff",
				"Modern Coffee Table", "object/tangible/furniture/modern/coffee_table_modern_style_01.iff",
				"Modern Couch (Style 1)", "object/tangible/furniture/modern/couch_modern_style_01.iff",
				"Modern Couch (Style 2)", "object/tangible/furniture/modern/couch_modern_style_02.iff",
				"Modern Dining Table", "object/tangible/furniture/modern/dining_table_modern_style_01.iff",
				"Modern End Table", "object/tangible/furniture/modern/end_table_large_modern_style_01.iff",
				"Modern Love Seat", "object/tangible/furniture/modern/love_seat_modern_style_01.iff"
			}
			
		},
		"Structure Deeds",
		{
			"Factional Bases",
			{
				"Generic Base 1", "object/tangible/deed/faction_perk/hq/hq_s01.iff",
				"Generic PVP Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_pvp.iff",
				"Generic Base 2", "object/tangible/deed/faction_perk/hq/hq_s02.iff",
				"Generic PVP Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_pvp.iff",
				"Generic Base 3", "object/tangible/deed/faction_perk/hq/hq_s03.iff",
				"Generic PVP Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_pvp.iff",
				"Generic Base 4", "object/tangible/deed/faction_perk/hq/hq_s04.iff",
				"Generic PVP Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_pvp.iff",
				"Generic Base 5", "object/tangible/deed/faction_perk/hq/hq_s05.iff",
				"Generic PVP Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_pvp.iff",
				"Imperial Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_imp.iff",
				"Imperial PVP Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_imp_pvp.iff",
				"Imperial Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_imp.iff",
				"Imperial PVP Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_imp_pvp.iff",
				"Imperial Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_imp.iff",
				"Imperial PVP Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_imp_pvp.iff",
				"Imperial Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_imp.iff",
				"Imperial PVP Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_imp_pvp.iff",
				"Imperial Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_imp.iff",
				"Imperial PVP Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_imp_pvp.iff",
				"Rebel Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_reb.iff",
				"Rebel PVP Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_reb_pvp.iff",
				"Rebel Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_reb.iff",
				"Rebel PVP Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_reb_pvp.iff",
				"Rebel Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_reb.iff",
				"Rebel PVP Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_reb_pvp.iff",
				"Rebel Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_reb.iff",
				"Rebel PVP Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_reb_pvp.iff",
				"Rebel Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_reb.iff",
				"Rebel PVP Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_reb_pvp.iff",
			},
			"Merchant Tent Deeds",
			{
				"Merchant Tent Deed (Style 1)", "object/tangible/deed/player_house_deed/merchant_tent_style_01_deed.iff",
				"Merchant Tent Deed (Style 2)", "object/tangible/deed/player_house_deed/merchant_tent_style_02_deed.iff",
				"Merchant Tent Deed (Style 3)", "object/tangible/deed/player_house_deed/merchant_tent_style_03_deed.iff"
			},
			"Installation Deeds",
			{
				"Harvester Deeds",
				{
					"Creature Harvester Deed", "object/tangible/deed/harvester_deed/harvester_creature_deed.iff",
					"Personal Flora Harvester Deed", "object/tangible/deed/harvester_deed/harvester_flora_deed.iff",
					"Heavy Flora Harvester Deed", "object/tangible/deed/harvester_deed/harvester_flora_deed_heavy.iff",
					"Medium Flora Harvester Deed", "object/tangible/deed/harvester_deed/harvester_flora_deed_medium.iff",
					"Personal Gas Harvester Deed", "object/tangible/deed/harvester_deed/harvester_gas_deed.iff",
					"Heavy Gas Harvester Deed", "object/tangible/deed/harvester_deed/harvester_gas_deed_heavy.iff",
					"Medium Gas Harvester Deed", "object/tangible/deed/harvester_deed/harvester_gas_deed_medium.iff",
					"Personal Liquid Harvester Deed", "object/tangible/deed/harvester_deed/harvester_liquid_deed.iff",
					"Heavy Liquid Harvester Deed", "object/tangible/deed/harvester_deed/harvester_liquid_deed_heavy.iff",
					"Medium Liquid Harvester Deed", "object/tangible/deed/harvester_deed/harvester_liquid_deed_medium.iff",
					"Personal Moisture Harvester Deed", "object/tangible/deed/harvester_deed/harvester_moisture_deed.iff",
					"Heavy Moisture Harvester Deed", "object/tangible/deed/harvester_deed/harvester_moisture_deed_heavy.iff",
					"Medium Moisture Harvester Deed", "object/tangible/deed/harvester_deed/harvester_moisture_deed_medium.iff",
					"Personal Mineral Harvester Deed", "object/tangible/deed/harvester_deed/harvester_ore_heavy_deed.iff",
					"Heavy Mineral Harvester Deed", "object/tangible/deed/harvester_deed/harvester_ore_s1_deed.iff",
					"Medium Mineral Harvester Deed", "object/tangible/deed/harvester_deed/harvester_ore_s2_deed.iff"
				},
				"Generator Deeds",
				{
					"Fusion Generator Deed", "object/tangible/deed/generator_deed/generator_fusion_deed.iff",
					"Photo Bio Generator Deed", "object/tangible/deed/generator_deed/generator_photo_bio_deed.iff",
					"Solar Generator Deed", "object/tangible/deed/generator_deed/generator_solar_deed.iff",
					"Wind Generator Deed", "object/tangible/deed/generator_deed/generator_wind_deed.iff",
				},
				"Factory Deeds",
				{
					"Clothing Factory Deed", "object/tangible/deed/factory_deed/factory_clothing_deed.iff",
					"Food Factory Deed", "object/tangible/deed/factory_deed/factory_food_deed.iff",
					"Item Factory Deed", "object/tangible/deed/factory_deed/factory_item_deed.iff",
					"Structure Factory Deed", "object/tangible/deed/factory_deed/factory_structure_deed.iff"
				}
			},
			"Generic Deeds",
			{
				"Player House Deeds",
				{
					"Large Generic House Deed", "object/tangible/deed/player_house_deed/generic_house_large_deed.iff",
					"Large Generic House Deed (Style 2)", "object/tangible/deed/player_house_deed/generic_house_large_style_02_deed.iff",
					"Medium Generic House Deed", "object/tangible/deed/player_house_deed/generic_house_medium_deed.iff",
					"Medium Generic House Deed (Style 2)", "object/tangible/deed/player_house_deed/generic_house_medium_style_02_deed.iff",
					"Small Generic House Deed", "object/tangible/deed/player_house_deed/generic_house_small_deed.iff",
					"Small Generic House Deed Floorplan 2", "object/tangible/deed/player_house_deed/generic_house_small_floor_02_deed.iff",
					"Small Generic House Deed (Style 2)", "object/tangible/deed/player_house_deed/generic_house_small_style_02_deed.iff",
					"Small Generic House Deed Floorplan 2 (Style 2)", "object/tangible/deed/player_house_deed/generic_house_small_style_02_floor_02_deed.iff",
					"Large Tatooine House Deed", "object/tangible/deed/player_house_deed/tatooine_house_large_deed.iff"
				},
				"City Deeds",
				{
					"Large Dantooine Garden", "object/tangible/deed/city_deed/garden_dantooine_lrg_01_deed.iff",
					"Medium Dantooine Garden", "object/tangible/deed/city_deed/garden_dantooine_med_01_deed.iff",
					"Small Dantooine Garden", "object/tangible/deed/city_deed/garden_dantooine_sml_01_deed.iff",
					"Large Dathomir Garden", "object/tangible/deed/city_deed/garden_dathomir_lrg_01_deed.iff",
					"Medium Dathomir Garden", "object/tangible/deed/city_deed/garden_dathomir_med_01_deed.iff",
					"Small Dathomir Garden", "object/tangible/deed/city_deed/garden_dathomir_sml_01_deed.iff",
					"Large Endor Garden", "object/tangible/deed/city_deed/garden_endor_lrg_01_deed.iff",
					"Medium Endor Garden", "object/tangible/deed/city_deed/garden_endor_med_01_deed.iff",
					"Small Endor Garden", "object/tangible/deed/city_deed/garden_endor_sml_01_deed.iff"	
				}
			},
			"Corellia Deeds",
			{
				"Player House Deeds",
				{
					"Corellian Guild Hall Deed", "object/tangible/deed/guild_deed/corellia_guild_deed.iff",
					"Large Corellian House Deed", "object/tangible/deed/player_house_deed/corellia_house_large_deed.iff",
					"Large Corellian House Deed (Style 2)", "object/tangible/deed/player_house_deed/corellia_house_large_style_02_deed.iff",
					"Medium Corellian House Deed", "object/tangible/deed/player_house_deed/corellia_house_medium_deed.iff",
					"Medium Corellian House Deed (Style 2)", "object/tangible/deed/player_house_deed/corellia_house_medium_style_02_deed.iff",
					"Small Corellian House Deed", "object/tangible/deed/player_house_deed/corellia_house_small_deed.iff",
					"Small Corellian House Deed Floorplan 2", "object/tangible/deed/player_house_deed/corellia_house_small_floor_02_deed.iff",
					"Small Corellian House Deed (Style 2)", "object/tangible/deed/player_house_deed/corellia_house_small_style_02_deed.iff",
					"Small Corellian House Deed Floorplan 2 (Style 2)", "object/tangible/deed/player_house_deed/corellia_house_small_style_02_floor_02_deed.iff"
				},
				"City Deeds",
				{
					"Corellia Bank Deed", "object/tangible/deed/city_deed/bank_corellia_deed.iff",
					"Corellia Cantina Deed", "object/tangible/deed/city_deed/cantina_corellia_deed.iff",
					"Corellia Garage Deed", "object/tangible/deed/city_deed/garage_corellia_deed.iff",
					"Corellia Shuttleport Deed", "object/tangible/deed/city_deed/shuttleport_corellia_deed.iff",
					"Corellia City Hall Deed", "object/tangible/deed/city_deed/cityhall_corellia_deed.iff",
					"Corellia Cloning Center Deed", "object/tangible/deed/city_deed/cloning_corellia_deed.iff",
					"Corellia Medical Center Deed", "object/tangible/deed/city_deed/hospital_corellia_deed.iff",
					"Corellia Theater Deed", "object/tangible/deed/city_deed/theater_corellia_deed.iff",
					"Large Corellia Garden (Style 1)", "object/tangible/deed/city_deed/garden_corellia_lrg_01_deed.iff",
					"Large Corellia Garden (Style 2)", "object/tangible/deed/city_deed/garden_corellia_lrg_02_deed.iff",
					"Large Corellia Garden (Style 3)", "object/tangible/deed/city_deed/garden_corellia_lrg_03_deed.iff",
					"Large Corellia Garden (Style 4)", "object/tangible/deed/city_deed/garden_corellia_lrg_04_deed.iff",
					"Large Corellia Garden (Style 5)", "object/tangible/deed/city_deed/garden_corellia_lrg_05_deed.iff",
					"Medium Corellia Garden (Style 1)", "object/tangible/deed/city_deed/garden_corellia_med_01_deed.iff",
					"Medium Corellia Garden (Style 2)", "object/tangible/deed/city_deed/garden_corellia_med_02_deed.iff",
					"Medium Corellia Garden (Style 3)", "object/tangible/deed/city_deed/garden_corellia_med_03_deed.iff",
					"Medium Corellia Garden (Style 4)", "object/tangible/deed/city_deed/garden_corellia_med_04_deed.iff",
					"Medium Corellia Garden (Style 5)", "object/tangible/deed/city_deed/garden_corellia_med_05_deed.iff",
					"Small Corellia Garden (Style 1)", "object/tangible/deed/city_deed/garden_corellia_sml_01_deed.iff",
					"Small Corellia Garden (Style 2)", "object/tangible/deed/city_deed/garden_corellia_sml_02_deed.iff",
					"Small Corellia Garden (Style 3)", "object/tangible/deed/city_deed/garden_corellia_sml_03_deed.iff",
					"Small Corellia Garden (Style 4)", "object/tangible/deed/city_deed/garden_corellia_sml_04_deed.iff",
					"Small Corellia Garden (Style 5)", "object/tangible/deed/city_deed/garden_corellia_sml_05_deed.iff"
				}
			},
			"Naboo Deeds",
			{
				"Player House Deeds",
				{
					"Naboo Guild Hall Deed", "object/tangible/deed/guild_deed/naboo_guild_deed.iff",
					"Large Naboo House Deed", "object/tangible/deed/player_house_deed/naboo_house_large_deed.iff",
					"Medium Naboo House Deed", "object/tangible/deed/player_house_deed/naboo_house_medium_deed.iff",
					"Medium Naboo House Deed (Style 2)", "object/tangible/deed/player_house_deed/naboo_house_medium_style_02_deed.iff",
					"Small Naboo House Deed", "object/tangible/deed/player_house_deed/naboo_house_small_deed.iff",
					"Small Naboo House Deed (Style 2)", "object/tangible/deed/player_house_deed/naboo_house_small_style_02_deed.iff"
				},
				"City Deeds",
				{
					"Naboo Bank Deed", "object/tangible/deed/city_deed/bank_naboo_deed.iff",
					"Naboo Cantina Deed", "object/tangible/deed/city_deed/cantina_naboo_deed.iff",
					"Naboo Garage Deed", "object/tangible/deed/city_deed/garage_naboo_deed.iff",
					"Naboo Shuttleport Deed", "object/tangible/deed/city_deed/shuttleport_naboo_deed.iff",
					"Naboo City Hall Deed", "object/tangible/deed/city_deed/cityhall_naboo_deed.iff",
					"Naboo Cloning Center Deed", "object/tangible/deed/city_deed/cloning_naboo_deed.iff",
					"Naboo Medical Center Deed", "object/tangible/deed/city_deed/hospital_naboo_deed.iff",
					"Naboo Theater Deed", "object/tangible/deed/city_deed/theater_naboo_deed.iff",
					"Large Naboo Garden (Style 1)", "object/tangible/deed/city_deed/garden_naboo_lrg_01_deed.iff",
					"Large Naboo Garden (Style 2)", "object/tangible/deed/city_deed/garden_naboo_lrg_02_deed.iff",
					"Large Naboo Garden (Style 3)", "object/tangible/deed/city_deed/garden_naboo_lrg_03_deed.iff",
					"Large Naboo Garden (Style 4)", "object/tangible/deed/city_deed/garden_naboo_lrg_04_deed.iff",
					"Large Naboo Garden (Style 5)", "object/tangible/deed/city_deed/garden_naboo_lrg_05_deed.iff",
					"Medium Naboo Garden (Style 1)", "object/tangible/deed/city_deed/garden_naboo_med_01_deed.iff",
					"Medium Naboo Garden (Style 2)", "object/tangible/deed/city_deed/garden_naboo_med_02_deed.iff",
					"Medium Naboo Garden (Style 3)", "object/tangible/deed/city_deed/garden_naboo_med_03_deed.iff",
					"Medium Naboo Garden (Style 4)", "object/tangible/deed/city_deed/garden_naboo_med_04_deed.iff",
					"Medium Naboo Garden (Style 5)", "object/tangible/deed/city_deed/garden_naboo_med_05_deed.iff",
					"Small Naboo Garden (Style 1)", "object/tangible/deed/city_deed/garden_naboo_sml_01_deed.iff",
					"Small Naboo Garden (Style 2)", "object/tangible/deed/city_deed/garden_naboo_sml_02_deed.iff",
					"Small Naboo Garden (Style 3)", "object/tangible/deed/city_deed/garden_naboo_sml_03_deed.iff",
					"Small Naboo Garden (Style 4)", "object/tangible/deed/city_deed/garden_naboo_sml_04_deed.iff",
					"Small Naboo Garden (Style 5)", "object/tangible/deed/city_deed/garden_naboo_sml_05_deed.iff"
				}
			},
			"Tatooine Deeds",
			{
				"Player House Deeds",
				{
					"Tatooine Guild Hall Deed", "object/tangible/deed/guild_deed/tatooine_guild_deed.iff",
					"Tatooine Guild Hall (Style 2) Deed", "object/tangible/deed/guild_deed/tatooine_guild_style_02_deed.iff",
					"Large Tatooine House Deed", "object/tangible/deed/player_house_deed/tatooine_house_large_deed.iff",
					"Medium Tatooine House Deed", "object/tangible/deed/player_house_deed/tatooine_house_medium_deed.iff",
					"Small Tatooine House Deed", "object/tangible/deed/player_house_deed/tatooine_house_small_deed.iff",
					"Small Tatooine House Deed (Style 2)", "object/tangible/deed/player_house_deed/tatooine_house_small_style_02_deed.iff"
				},
				"City Deeds",
				{
					"Tatooine Bank Deed", "object/tangible/deed/city_deed/bank_tatooine_deed.iff",
					"Tatooine Cantina Deed", "object/tangible/deed/city_deed/cantina_tatooine_deed.iff",
					"Tatooine Garage Deed", "object/tangible/deed/city_deed/garage_tatooine_deed.iff",
					"Tatooine Shuttleport Deed", "object/tangible/deed/city_deed/shuttleport_tatooine_deed.iff",
					"Tatooine City Hall Deed", "object/tangible/deed/city_deed/cityhall_tatooine_deed.iff",
					"Tatooine Cloning Center Deed", "object/tangible/deed/city_deed/cloning_tatooine_deed.iff",
					"Tatooine Medical Center Deed", "object/tangible/deed/city_deed/hospital_tatooine_deed.iff",
					"Tatooine Theater Deed", "object/tangible/deed/city_deed/theater_tatooine_deed.iff",
					"Large Tatooine Garden (Style 1)", "object/tangible/deed/city_deed/garden_tatooine_lrg_01_deed.iff",
					"Large Tatooine Garden (Style 2)", "object/tangible/deed/city_deed/garden_tatooine_lrg_02_deed.iff",
					"Large Tatooine Garden (Style 3)", "object/tangible/deed/city_deed/garden_tatooine_lrg_03_deed.iff",
					"Large Tatooine Garden (Style 4)", "object/tangible/deed/city_deed/garden_tatooine_lrg_04_deed.iff",
					"Large Tatooine Garden (Style 5)", "object/tangible/deed/city_deed/garden_tatooine_lrg_05_deed.iff",
					"Medium Tatooine Garden (Style 1)", "object/tangible/deed/city_deed/garden_tatooine_med_01_deed.iff",
					"Medium Tatooine Garden (Style 2)", "object/tangible/deed/city_deed/garden_tatooine_med_02_deed.iff",
					"Medium Tatooine Garden (Style 3)", "object/tangible/deed/city_deed/garden_tatooine_med_03_deed.iff",
					"Medium Tatooine Garden (Style 4)", "object/tangible/deed/city_deed/garden_tatooine_med_04_deed.iff",
					"Medium Tatooine Garden (Style 5)", "object/tangible/deed/city_deed/garden_tatooine_med_05_deed.iff",
					"Small Tatooine Garden (Style 1)", "object/tangible/deed/city_deed/garden_tatooine_sml_01_deed.iff",
					"Small Tatooine Garden (Style 2)", "object/tangible/deed/city_deed/garden_tatooine_sml_02_deed.iff",
					"Small Tatooine Garden (Style 3)", "object/tangible/deed/city_deed/garden_tatooine_sml_03_deed.iff",
					"Small Tatooine Garden (Style 4)", "object/tangible/deed/city_deed/garden_tatooine_sml_04_deed.iff",
					"Small Tatooine Garden (Style 5)", "object/tangible/deed/city_deed/garden_tatooine_sml_05_deed.iff"
				}
			}
		}
	}
}

ObjectTemplates:addTemplate(object_tangible_terminal_terminal_character_builder, "object/tangible/terminal/terminal_character_builder.iff")
