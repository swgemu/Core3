heavy_weapons = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {
		{itemTemplate = "heavy_rocket_launcher", weight = 1000000},
		{itemTemplate = "heavy_acid_beam", weight = 1000000},
		{itemTemplate = "heavy_lightning_beam", weight = 1000000},
		{itemTemplate = "heavy_particle_beam", weight = 1000000},
		{itemTemplate = "rifle_acid_beam", weight = 2000000},
		{itemTemplate = "rifle_flame_thrower", weight = 2000000},
		{itemTemplate = "rifle_lightning", weight = 2000000}
	}
}

addLootGroupTemplate("heavy_weapons", heavy_weapons)
