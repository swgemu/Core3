composit_armor_looted = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{itemTemplate = "composit_armor_helmet", weight = 1000000},
		{itemTemplate = "composit_armor_chest_plate", weight = 1000000},
		{itemTemplate = "composit_armor_leggings", weight = 1000000},
		{itemTemplate = "composit_armor_boots", weight = 1100000},
		{itemTemplate = "composit_armor_gloves", weight = 1100000},
		{itemTemplate = "composit_armor_bracer_l", weight = 1200000},
		{itemTemplate = "composit_armor_bracer_r", weight = 1200000},
		{itemTemplate = "composit_armor_bicep_l", weight = 1200000},
		{itemTemplate = "composit_armor_bicep_r", weight = 1200000},
	}
}

addLootGroupTemplate("composit_armor_looted", composit_armor_looted)
