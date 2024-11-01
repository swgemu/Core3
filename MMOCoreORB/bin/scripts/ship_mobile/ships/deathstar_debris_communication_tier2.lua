deathstar_debris_communication_tier2 = ShipAgent:new {
	template = "merchant_cruiser_light_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "bomber",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian", "nym"},

	color1 = 6,
	color2 = 40,
	texture = 0,
	questLoot = "debris_cult_hostage",
	appearance = "deathstar_debris_cultist",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(deathstar_debris_communication_tier2, "deathstar_debris_communication_tier2")
