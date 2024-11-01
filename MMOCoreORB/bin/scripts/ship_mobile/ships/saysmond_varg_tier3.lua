saysmond_varg_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "fighter",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"rsf"},

	color1 = 8,
	color2 = 22,
	texture = 5,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(saysmond_varg_tier3, "saysmond_varg_tier3")
