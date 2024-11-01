freighterlight_rebel = ShipAgent:new {
	template = "freighterlight_tier3",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier1",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -5,
	appearance = "rebel_pilot",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterlight_rebel, "freighterlight_rebel")
