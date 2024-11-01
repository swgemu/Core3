tiedecimator_ace = ShipAgent:new {
	template = "decimator_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "fighter",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -6,
	rebelFactionReward = 3,
	appearance = "imperial_ace",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tiedecimator_ace, "tiedecimator_ace")
