imperial_boss = ShipAgent:new {
	template = "tieoppressor_tier2",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -8,
	rebelFactionReward = 4,
	appearance = "imperial_ace",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imperial_boss, "imperial_boss")
