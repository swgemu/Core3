rebel_saboteur = ShipAgent:new {
	template = "awing_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "bomber",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "civilian", "merchant"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 25,
	rebelFactionReward = -49,

	color1 = 63,
	color2 = 3,
	texture = 3,
	appearance = "rebel_pilot",
}

ShipAgentTemplates:addShipAgentTemplate(rebel_saboteur, "rebel_saboteur")
