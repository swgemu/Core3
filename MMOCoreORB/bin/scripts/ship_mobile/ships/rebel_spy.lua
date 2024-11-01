rebel_spy = ShipAgent:new {
	template = "tiefighter_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "civilian", "merchant"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 27,
	rebelFactionReward = -54,

	color1 = 4,
	color2 = 47,
	texture = 3,
	appearance = "rebel_pilot",
}

ShipAgentTemplates:addShipAgentTemplate(rebel_spy, "rebel_spy")
