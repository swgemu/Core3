test_loot_item = {
	minimumLevel = 0,
	maximumLevel = -1,
	chance = 100.0, -- min 0.00001
	directObjectTemplate = "", -- if this value is set all the below values are ignored
	
	draftSchematic = "object/draft_schematic/clothing/clothing_armor_composite_bicep_l.iff",
	
	experimentalSubGroupTitles = {"hit_points", "armor_effectiveness", "armor_integrity", "armor_health_encumbrance", "armor_action_encumbrance", "armor_mind_encumbrance", "armor_rating", "armor_special_type", "armor_special_effectiveness", "armor_special_integrity"},
	experimentalMin = {1000, 1, 100, 20, 20, 20, 1, 64, 1, 20},
	experimentalMax = {1000, 5, 1000, 0, 0, 0, 1, 64, 15, 50},
	
	--{max, min} AMAZINGSUCCESS = 0 GREATSUCCESS = 1 GOODSUCCESS = 2 MODERATESUCCESS = 3 SUCCESS = 4 MARGINALSUCCESS = 5 OK = 6 BARELYSUCCESSFUL = 7 CRITICALFAILURE = 8
	qualityRangeMin = CRITICALFAILURE,
	qualityRangeMax = AMAZINGSUCCESS,
	
	customizationStringNames = {"/private/index_color_1"},
   	customizationValues = { {0, 1} } -- random value ranges for each customization string name
}

addLootItemTemplate("test_loot_item", test_loot_item)
