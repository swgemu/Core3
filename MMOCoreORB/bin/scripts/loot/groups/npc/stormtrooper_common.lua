stormtrooper_common = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {
		{itemTemplate = "painting_bw_stormtrooper", weight = 2375000},
		{itemTemplate = "painting_han_wanted", weight = 2375000},
		{itemTemplate = "painting_leia_wanted", weight = 2375000},
		{itemTemplate = "painting_luke_wanted", weight = 2375000},
		{groupTemplate = "weapon_component", weight = 250000},
		{groupTemplate = "chemistry_component", weight = 250000}
	}
}

addLootGroupTemplate("stormtrooper_common", stormtrooper_common)