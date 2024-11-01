imperial_worker_ship = ShipAgent:new {
	template = "tieoppressor_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 260,
	maxCredits = 575,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial", "civilian", "merchant"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -60,
	rebelFactionReward = 30,
	appearance = "imperial_officer",
}

ShipAgentTemplates:addShipAgentTemplate(imperial_worker_ship, "imperial_worker_ship")
