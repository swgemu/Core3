kobola_common = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {
		{itemTemplate = "ore_recycler_schematic", weight = 1000000},
		{itemTemplate = "tumble_blender_schematic", weight = 1500000},
		{itemTemplate = "fireworks_packager", weight = 1000000},
		{itemTemplate = "firework_casing", weight = 1000000},
		{itemTemplate = "packaged_flash_powder", weight = 1500000},
		{itemTemplate = "skill_buff_onehandmelee_accuracy", weight = 1000000},
		{itemTemplate = "skill_buff_onehandmelee_speed", weight = 1000000},
		{groupTemplate = "wearables_common", weight = 2000000},		
	}
}

addLootGroupTemplate("kobola_common", kobola_common)
