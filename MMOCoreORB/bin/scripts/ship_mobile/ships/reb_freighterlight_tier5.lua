reb_freighterlight_tier5 = ShipAgent:new {
	template = "freighterlight_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier4",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -50,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_freighterlight_tier5, "reb_freighterlight_tier5")
