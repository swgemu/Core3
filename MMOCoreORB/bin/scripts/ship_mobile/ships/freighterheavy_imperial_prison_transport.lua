freighterheavy_imperial_prison_transport = ShipAgent:new {
	template = "freighterheavy_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier1",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -40,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterheavy_imperial_prison_transport, "freighterheavy_imperial_prison_transport")
