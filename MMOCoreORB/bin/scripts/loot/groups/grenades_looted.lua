grenades_looted = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{itemTemplate = "grenade_cryoban", weight = 1500000},
		{itemTemplate = "grenade_fragmentation_light", weight = 2000000},
		{itemTemplate = "grenade_fragmentation", weight = 1500000},
		{itemTemplate = "grenade_glop", weight = 1500000},
		{itemTemplate = "grenade_imperial_detonator", weight = 1250000},
		{itemTemplate = "grenade_proton", weight = 1000000},
		{itemTemplate = "grenade_thermal_detonator", weight = 1250000}
	}
}

addLootGroupTemplate("grenades_looted", grenades_looted)
