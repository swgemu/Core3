tieaggressor_ace = ShipAgent:new {
	template = "tieaggressor_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 160,

	lootChance = 0.272,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -4,
	rebelFactionReward = 2,
	appearance = "imperial_ace",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tieaggressor_ace, "tieaggressor_ace")
