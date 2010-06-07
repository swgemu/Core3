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
		"Furniture",
		{
			"Elegant Chair", "object/tangible/furniture/elegant/shared_chair_s01.iff",
			"Elegant Coffee Table", "object/tangible/furniture/elegant/shared_coffee_table_s01.iff"
		},
		"Structure Deeds",
		{
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