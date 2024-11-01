tiebomber_ace_tier3 = ShipAgent:new {
	template = "tiebomber_tier3",
	pilotTemplate = "bomber_tier4",
	shipType = "bomber",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -23,
	rebelFactionReward = 12,
	appearance = "imperial_ace",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tiebomber_ace_tier3, "tiebomber_ace_tier3")
