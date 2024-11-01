imp_freighterheavy_tier3 = ShipAgent:new {
	template = "freighterheavy_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier5",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -30,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_freighterheavy_tier3, "imp_freighterheavy_tier3")
