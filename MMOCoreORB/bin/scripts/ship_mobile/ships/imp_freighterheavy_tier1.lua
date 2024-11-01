imp_freighterheavy_tier1 = ShipAgent:new {
	template = "freighterheavy_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier5",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -5,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_freighterheavy_tier1, "imp_freighterheavy_tier1")
