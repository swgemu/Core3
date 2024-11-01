colonel_hend_shuttle_tier3 = ShipAgent:new {
	template = "lambdashuttle_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "transport",

	experience = 3200,

	lootChance = 0.375,
	lootRolls = 1,
	lootTable = "space_rebel_tier1",

	minCredits = 58,
	maxCredits = 736,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"civilian", "rebel"},
	enemyFactions = {"imperial", "hutt", "pirate"},
	imperialFactionReward = 32,
	rebelFactionReward = -64,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(colonel_hend_shuttle_tier3, "colonel_hend_shuttle_tier3")
