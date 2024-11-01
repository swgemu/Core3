tieaggressor_uvqolo = ShipAgent:new {
	template = "tieaggressor_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "fighter",

	experience = 10737.42,

	lootChance = 0.208,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -115,
	rebelFactionReward = 58,
	appearance = "imperial_inquisitor",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tieaggressor_uvqolo, "tieaggressor_uvqolo")
