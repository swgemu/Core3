tiebomber_tier4 = ShipAgent:new {
	template = "tiebomber_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "bomber",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 260,
	maxCredits = 575,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -60,
	rebelFactionReward = 30,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tiebomber_tier4, "tiebomber_tier4")
