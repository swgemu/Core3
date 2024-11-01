tieaggressor_ace_tier3 = ShipAgent:new {
	template = "tieaggressor_tier3",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 2048,

	lootChance = 0.24,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -25,
	rebelFactionReward = 13,
	appearance = "imperial_ace",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tieaggressor_ace_tier3, "tieaggressor_ace_tier3")
