reb_unmaned_xwing_tier2 = ShipAgent:new {
	template = "xwing_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 6,
	rebelFactionReward = -11,

	color1 = 40,
	color2 = 10,
	formationLocation = 2,
	appearance = "rebel_pilot",
}

ShipAgentTemplates:addShipAgentTemplate(reb_unmaned_xwing_tier2, "reb_unmaned_xwing_tier2")
