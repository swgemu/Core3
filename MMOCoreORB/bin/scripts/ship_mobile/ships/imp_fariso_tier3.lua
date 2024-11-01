imp_fariso_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "bomber",

	experience = 3200,

	lootChance = 0.375,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 58,
	maxCredits = 736,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -64,
	rebelFactionReward = 32,
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_fariso_tier3, "imp_fariso_tier3")
