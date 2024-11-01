vylukh_clan_elite_tier2 = ShipAgent:new {
	template = "awing_tier3",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt"},

	color1 = 1,
	color2 = 14,
	texture = 2,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(vylukh_clan_elite_tier2, "vylukh_clan_elite_tier2")
