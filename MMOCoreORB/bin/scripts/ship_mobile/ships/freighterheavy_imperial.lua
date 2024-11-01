freighterheavy_imperial = ShipAgent:new {
	template = "freighterheavy_tier3",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier1",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -5,
	questLoot = "general_cargo",
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterheavy_imperial, "freighterheavy_imperial")
