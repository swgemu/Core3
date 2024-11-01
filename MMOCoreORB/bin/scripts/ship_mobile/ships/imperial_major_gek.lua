imperial_major_gek = ShipAgent:new {
	template = "tieinterceptor_tier2",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -7,
	rebelFactionReward = 4,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imperial_major_gek, "imperial_major_gek")
