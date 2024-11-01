reb_xwing_cadet_tier1 = ShipAgent:new {
	template = "xwing_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 110,

	lootChance = 0.187,
	lootRolls = 1,
	lootTable = "space_rebel_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 2,
	rebelFactionReward = -3,

	color1 = 40,
	color2 = 10,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_xwing_cadet_tier1, "reb_xwing_cadet_tier1")
