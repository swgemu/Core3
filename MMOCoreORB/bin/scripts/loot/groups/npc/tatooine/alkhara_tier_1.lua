--Automatically generated by SWGEmu Spawn Tool v0.12 loot editor.

alkhara_tier_1 = {
	description = "",
	minimumLevel = 0,
	maximumLevel = -1,
	lootItems = {
		{groupTemplate = "alkhara_common", weight = 200000},
		{groupTemplate = "color_crystals", weight = 300000},
		{groupTemplate = "junk", weight = 1500000},
		{groupTemplate = "loot_kit_parts", weight = 850000},
		{groupTemplate = "ranged_weapons", weight = 4000000},
		{groupTemplate = "tailor_components", weight = 800000},
		{groupTemplate = "wearables_common", weight = 1100000},
		{groupTemplate = "resource_gemstone", weight = 250000},
		{groupTemplate = "resource_metal", weight = 250000},
		{groupTemplate = "resource_ore", weight = 250000},
		{groupTemplate = "resource_water", weight = 250000},
		{groupTemplate = "crafting_component", weight = 250000},
	}
}

addLootGroupTemplate("alkhara_tier_1", alkhara_tier_1)

--[[
mobiles:
	scripts/mobile/tatooine/alkhara_bandit.lua	13
	scripts/mobile/tatooine/alkhara_bandit_king.lua	22
	scripts/mobile/tatooine/alkhara_champion.lua	20
	scripts/mobile/tatooine/alkhara_lieutenant.lua	16
]]--