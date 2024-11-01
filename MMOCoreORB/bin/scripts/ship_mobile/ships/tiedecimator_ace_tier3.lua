tiedecimator_ace_tier3 = ShipAgent:new {
	template = "decimator_tier3",
	pilotTemplate = "heavy_tier4",
	shipType = "fighter",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -42,
	rebelFactionReward = 21,
	appearance = "imperial_ace",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tiedecimator_ace_tier3, "tiedecimator_ace_tier3")
