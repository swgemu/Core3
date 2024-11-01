lambdashuttle_rebel_tier3_1_a_spies = ShipAgent:new {
	template = "lambdashuttle_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "bomber",

	experience = 3200,

	lootChance = 0.375,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 58,
	maxCredits = 736,

	aggressive = 0,

	spaceFaction = "rebel",
	imperialFactionReward = 32,
	rebelFactionReward = -64,
	appearance = "rebel_pilot",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(lambdashuttle_rebel_tier3_1_a_spies, "lambdashuttle_rebel_tier3_1_a_spies")
