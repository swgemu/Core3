composite_armor_looted = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{itemTemplate = "composite_armor_helmet", weight = 1000000},
		{itemTemplate = "composite_armor_chest_plate", weight = 1000000},
		{itemTemplate = "composite_armor_leggings", weight = 1000000},
		{itemTemplate = "composite_armor_boots", weight = 1100000},
		{itemTemplate = "composite_armor_gloves", weight = 1100000},
		{itemTemplate = "composite_armor_bracer_l", weight = 1200000},
		{itemTemplate = "composite_armor_bracer_r", weight = 1200000},
		{itemTemplate = "composite_armor_bicep_l", weight = 1200000},
		{itemTemplate = "composite_armor_bicep_r", weight = 1200000},
	}
}

addLootGroupTemplate("composite_armor_looted", composite_armor_looted)
