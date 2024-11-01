rebel_saboteur_tier3 = ShipAgent:new {
	template = "awing_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "bomber",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "civilian", "merchant"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 12,
	rebelFactionReward = -23,

	color1 = 63,
	color2 = 3,
	texture = 3,
	appearance = "rebel_pilot",
}

ShipAgentTemplates:addShipAgentTemplate(rebel_saboteur_tier3, "rebel_saboteur_tier3")
