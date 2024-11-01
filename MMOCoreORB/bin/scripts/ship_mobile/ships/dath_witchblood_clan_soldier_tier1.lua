dath_witchblood_clan_soldier_tier1 = ShipAgent:new {
	template = "hutt_medium_s02_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 59,
	color2 = 59,
	texture = 5,
	questLoot = "witchblood_rallyinfo",
	appearance = "witchblood_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dath_witchblood_clan_soldier_tier1, "dath_witchblood_clan_soldier_tier1")
