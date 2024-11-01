tieinterceptor = ShipAgent:new {
	template = "tieinterceptor_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 90,

	lootChance = 0.153,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -3,
	rebelFactionReward = 2,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tieinterceptor, "tieinterceptor")
