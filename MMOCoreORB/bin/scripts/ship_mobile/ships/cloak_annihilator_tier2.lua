cloak_annihilator_tier2 = ShipAgent:new {
	template = "ywing_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "bomber",

	experience = 420,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "corsec", "merchant", "civilian", "rsf"},
	color2 = 42,
	formationLocation = 2,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(cloak_annihilator_tier2, "cloak_annihilator_tier2")
