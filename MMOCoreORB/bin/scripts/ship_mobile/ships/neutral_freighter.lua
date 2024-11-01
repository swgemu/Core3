neutral_freighter = ShipAgent:new {
	template = "freighterlight_tier3",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "true_neutral",
	questLoot = "rebel_cargo",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(neutral_freighter, "neutral_freighter")
