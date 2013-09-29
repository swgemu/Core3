flail_common = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {
		{itemTemplate = "skill_buff_carbine_accuracy", weight = 2500000},
		{itemTemplate = "skill_buff_carbine_speed", weight = 2500000},
		{itemTemplate = "skill_buff_polearm_accuracy", weight = 2500000},
		{itemTemplate = "skill_buff_polearm_speed", weight = 2500000}
	}
}

addLootGroupTemplate("flail_common", flail_common)