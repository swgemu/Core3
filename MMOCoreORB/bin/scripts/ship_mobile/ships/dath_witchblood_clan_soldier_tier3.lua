dath_witchblood_clan_soldier_tier3 = ShipAgent:new {
	template = "hutt_medium_s02_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 120,
	maxCredits = 294,

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

ShipAgentTemplates:addShipAgentTemplate(dath_witchblood_clan_soldier_tier3, "dath_witchblood_clan_soldier_tier3")
