reb_freightermedium_tier1 = ShipAgent:new {
	template = "freightermedium_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier4",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -5,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_freightermedium_tier1, "reb_freightermedium_tier1")
