--Automatically generated by SWGEmu Spawn Tool v0.12 loot editor.

weequay_tier_1 = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{groupTemplate = "color_crystals", weight = 300000},
		{groupTemplate = "junk", weight = 2200000},
		{groupTemplate = "loot_kit_parts", weight = 1400000},
		{groupTemplate = "printer_parts", weight = 700000},
		{groupTemplate = "tailor_components", weight = 900000},
		{groupTemplate = "wearables_common", weight = 1300000},
		{groupTemplate = "weequay_common", weight = 200000},
		{groupTemplate = "resource_gemstone", weight = 250000},
		{groupTemplate = "resource_metal", weight = 250000},
		{groupTemplate = "resource_ore", weight = 250000},
		{groupTemplate = "resource_water", weight = 250000},
		{groupTemplate = "melee_weapons_common", weight = 1000000},
		{groupTemplate = "ranged_weapons_common", weight = 1000000},
	}
}

addLootGroupTemplate("weequay_tier_1", weequay_tier_1)

--[[
mobiles:
	scripts/mobile/tatooine/weequay_captain.lua	19
	scripts/mobile/tatooine/weequay_champion.lua	12
	scripts/mobile/tatooine/weequay_soldier.lua	10
	scripts/mobile/tatooine/weequay_thug.lua	9
	scripts/mobile/tatooine/weequay_zealot.lua	11
]]--