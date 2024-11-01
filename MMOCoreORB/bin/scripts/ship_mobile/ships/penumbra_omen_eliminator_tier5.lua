penumbra_omen_eliminator_tier5 = ShipAgent:new {
	template = "hutt_medium_s02_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "bomber",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "rsf", "corsec", "valarian"},

	color1 = 2,
	color2 = 3,
	texture = 2,
	formationLocation = 3,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(penumbra_omen_eliminator_tier5, "penumbra_omen_eliminator_tier5")
