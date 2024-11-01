tieaggressor_inquisitor_tier3 = ShipAgent:new {
	template = "tieaggressor_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 2048,

	lootChance = 0.24,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -30,
	rebelFactionReward = 15,
	appearance = "imperial_inquisitor",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tieaggressor_inquisitor_tier3, "tieaggressor_inquisitor_tier3")
