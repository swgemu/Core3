--Automatically generated by SWGEmu Spawn Tool v0.12 loot editor.

hidden_daggers_tier_1 = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{groupTemplate = "hidden_dagger_common", weight = 1800000},
		{groupTemplate = "junk", weight = 2800000},
		{groupTemplate = "loot_kit_parts", weight = 1200000},
		{groupTemplate = "tailor_components", weight = 600000},
		{groupTemplate = "wearables_all", weight = 600000},
		{groupTemplate = "resource_gemstone", weight = 250000},
		{groupTemplate = "resource_metal", weight = 250000},
		{groupTemplate = "resource_ore", weight = 250000},
		{groupTemplate = "resource_water", weight = 250000},
		{groupTemplate = "melee_weapons_common", weight = 1000000},
		{groupTemplate = "ranged_weapons_common", weight = 1000000},
	}
}

addLootGroupTemplate("hidden_daggers_tier_1", hidden_daggers_tier_1)

--[[
mobiles:
	scripts/mobile/corellia/hidden_daggers_activist.lua	9
	scripts/mobile/corellia/hidden_daggers_dissident.lua	11
	scripts/mobile/corellia/hidden_daggers_extremist.lua	13
	scripts/mobile/corellia/hidden_daggers_leader.lua	18
	scripts/mobile/corellia/hidden_daggers_lieutenant.lua	15
]]--