rebel_officer_common = {
	description = "",
	minimumLevel = 0,
	maximumLevel = 0,
	lootItems = {
		{itemTemplate = "radar_screen_schematic", weight = 3250000},
		{itemTemplate = "technical_console_schematic_1", weight = 3250000},
		{itemTemplate = "technical_console_schematic_2", weight = 3000000},
		{groupTemplate = "weapon_component", weight = 250000},
		{groupTemplate = "chemistry_component", weight = 250000}
	}
}

addLootGroupTemplate("rebel_officer_common", rebel_officer_common)