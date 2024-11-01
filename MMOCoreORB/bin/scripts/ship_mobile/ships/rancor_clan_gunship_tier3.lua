rancor_clan_gunship_tier3 = ShipAgent:new {
	template = "hutt_heavy_s01_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "fighter",

	experience = 4259.84,

	lootChance = 0.182,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 280,
	maxCredits = 650,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "corsec", "rsf", "borvo", "nym"},

	color1 = 25,
	color2 = 59,
	texture = 3,
	appearance = "rancor_clan_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rancor_clan_gunship_tier3, "rancor_clan_gunship_tier3")
