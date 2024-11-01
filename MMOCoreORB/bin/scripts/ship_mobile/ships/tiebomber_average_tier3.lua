tiebomber_average_tier3 = ShipAgent:new {
	template = "tiebomber_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "bomber",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -28,
	rebelFactionReward = 14,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tiebomber_average_tier3, "tiebomber_average_tier3")
