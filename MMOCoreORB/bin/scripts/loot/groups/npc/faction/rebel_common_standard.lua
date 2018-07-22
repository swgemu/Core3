rebel_common_standard = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{groupTemplate = "junk", weight = 3750000},
		{groupTemplate = "loot_kit_parts", weight = 1000000},
		{groupTemplate = "tailor_components", weight = 1000000},
		{groupTemplate = "wearables_all", weight = 1000000},
		{groupTemplate = "clothing_attachments", weight = 250000},
		{groupTemplate = "armor_attachments", weight = 250000},
		{groupTemplate = "ranged_weapons_medium", weight = 1000000},
		{groupTemplate = "melee_weapons_medium", weight = 1000000},
		{groupTemplate = "ranged_weapons_rare", weight = 250000},
		{groupTemplate = "melee_weapons_rare", weight = 250000},
		{groupTemplate = "weapon_component", weight = 200000},
		{groupTemplate = "weapon_component_advanced", weight = 50000},
	}
}

addLootGroupTemplate("rebel_common_standard", rebel_common_standard)
