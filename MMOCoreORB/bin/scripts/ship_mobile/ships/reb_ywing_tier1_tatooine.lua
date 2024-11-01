reb_ywing_tier1_tatooine = ShipAgent:new {
	template = "ywing_tier1",
	pilotTemplate = "bomber_tier1",
	shipType = "bomber",

	experience = 105,

	lootChance = 0.1785,
	lootRolls = 1,
	lootTable = "space_story_tatooine_rebel",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 2,
	rebelFactionReward = -3,
	color2 = 42,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_ywing_tier1_tatooine, "reb_ywing_tier1_tatooine")
