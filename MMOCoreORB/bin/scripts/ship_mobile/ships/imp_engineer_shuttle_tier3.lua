imp_engineer_shuttle_tier3 = ShipAgent:new {
	template = "transport_science_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -64,
	rebelFactionReward = 32,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_engineer_shuttle_tier3, "imp_engineer_shuttle_tier3")
