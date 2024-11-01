hiddendaggers_killer = ShipAgent:new {
	template = "xwing_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 110,

	lootChance = 0.187,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "rsf", "corsec"},

	color1 = 33,
	color2 = 55,
	texture = 2,
	appearance = "hiddendagger_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hiddendaggers_killer, "hiddendaggers_killer")
