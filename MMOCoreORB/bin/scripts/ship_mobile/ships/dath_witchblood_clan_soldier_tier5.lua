dath_witchblood_clan_soldier_tier5 = ShipAgent:new {
	template = "hutt_medium_s02_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 425,
	maxCredits = 825,

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

ShipAgentTemplates:addShipAgentTemplate(dath_witchblood_clan_soldier_tier5, "dath_witchblood_clan_soldier_tier5")
