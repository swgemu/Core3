mummer_common = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {
		{itemTemplate = "skill_buff_heavy_weapon_accuracy", weight = 1000000},
		{itemTemplate = "skill_buff_heavy_weapon_speed", weight = 1000000},
		{itemTemplate = "skill_buff_melee_accuracy", weight = 1000000},
		{itemTemplate = "skill_buff_melee_defense", weight = 1000000},
		{itemTemplate = "skill_buff_pistol_accuracy", weight = 1000000},
		{itemTemplate = "skill_buff_pistol_speed", weight = 1000000},
		{itemTemplate = "skill_buff_ranged_accuracy", weight = 1000000},
		{itemTemplate = "skill_buff_ranged_defense", weight = 1000000},
		{itemTemplate = "skill_buff_thrown_accuracy", weight = 1000000},
		{itemTemplate = "skill_buff_thrown_speed", weight = 1000000}		
	}
}

addLootGroupTemplate("mummer_common", mummer_common)
