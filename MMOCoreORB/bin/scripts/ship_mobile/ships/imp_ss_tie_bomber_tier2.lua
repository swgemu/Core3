imp_ss_tie_bomber_tier2 = ShipAgent:new {
	template = "tiebomber_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "bomber",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_imperial_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -11,
	rebelFactionReward = 6,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_ss_tie_bomber_tier2, "imp_ss_tie_bomber_tier2")
