imp_tie_bomber_tier1_naboo = ShipAgent:new {
	template = "tiebomber_tier1",
	pilotTemplate = "bomber_tier1",
	shipType = "bomber",

	experience = 110,

	lootChance = 0.187,
	lootRolls = 1,
	lootTable = "space_story_naboo_imperial",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -3,
	rebelFactionReward = 2,
	formationLocation = 2,
	appearance = "imperial_pilot",

	tauntType = "imperial_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imp_tie_bomber_tier1_naboo, "imp_tie_bomber_tier1_naboo")
