gernades_looted = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{itemTemplate = "gernade_cryoban", weight = 1500000},
		{itemTemplate = "gernade_fragmentation_light", weight = 2000000},
		{itemTemplate = "gernade_fragmentation", weight = 1500000},
		{itemTemplate = "gernade_glop", weight = 1500000},
		{itemTemplate = "gernade_imperial_detonator", weight = 1250000},
		{itemTemplate = "gernade_proton", weight = 1000000},
		{itemTemplate = "gernade_thermal_detonator", weight = 1250000}
	}
}

addLootGroupTemplate("gernades_looted", gernades_looted)
