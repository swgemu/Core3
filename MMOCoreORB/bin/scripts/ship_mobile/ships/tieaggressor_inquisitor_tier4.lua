tieaggressor_inquisitor_tier4 = ShipAgent:new {
	template = "tieaggressor_tier4",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 5242.88,

	lootChance = 0.224,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 275,
	maxCredits = 600,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -65,
	rebelFactionReward = 33,
	appearance = "imperial_inquisitor",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tieaggressor_inquisitor_tier4, "tieaggressor_inquisitor_tier4")
