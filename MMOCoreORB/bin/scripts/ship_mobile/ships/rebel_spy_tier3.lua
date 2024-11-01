rebel_spy_tier3 = ShipAgent:new {
	template = "tiefighter_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "civilian", "merchant"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 13,
	rebelFactionReward = -25,

	color1 = 4,
	color2 = 47,
	texture = 3,
	appearance = "rebel_pilot",
}

ShipAgentTemplates:addShipAgentTemplate(rebel_spy_tier3, "rebel_spy_tier3")
