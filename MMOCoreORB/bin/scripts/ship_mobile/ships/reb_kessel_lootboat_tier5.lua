reb_kessel_lootboat_tier5 = ShipAgent:new {
	template = "rebel_gunboat_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "fighter",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_kessel_rebel",

	minCredits = 525,
	maxCredits = 1075,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 192,
	rebelFactionReward = -383,
	appearance = "rebel_pilot",
}

ShipAgentTemplates:addShipAgentTemplate(reb_kessel_lootboat_tier5, "reb_kessel_lootboat_tier5")
