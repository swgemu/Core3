cloak_leader_decoy_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "fighter",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "corsec", "merchant", "civilian", "rsf"},

	color1 = 4,
	color2 = 3,
	texture = 2,
	formationLocation = 2,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(cloak_leader_decoy_tier3, "cloak_leader_decoy_tier3")
