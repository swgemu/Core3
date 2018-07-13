jawa_common = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{itemTemplate = "jawa_beads", weight = 3000000},
		{groupTemplate = "wearables_common", weight = 6500000},
		{groupTemplate = "weapon_component", weight = 250000},
		{groupTemplate = "chemistry_component", weight = 250000}
	}
}

addLootGroupTemplate("jawa_common", jawa_common)
