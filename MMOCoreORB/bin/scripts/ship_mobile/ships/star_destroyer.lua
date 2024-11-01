star_destroyer = ShipAgent:new {
	template = "star_destroyer",
	pilotTemplate = "heavy_tier5",
	shipType = "capital",

	experience = 50000,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier1",

	minCredits = 1840,
	maxCredits = 23000,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -200,
	rebelFactionReward = 500,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(star_destroyer, "star_destroyer")
