reb_bwing_boss = ShipAgent:new {
	template = "bwing_tier5",
	pilotTemplate = "bomber_tier5",
	shipType = "fighter",

	experience = 8053.06,

	lootChance = 0.156,
	lootRolls = 1,
	lootTable = "space_rebel_tier5",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 58,
	rebelFactionReward = -115,

	color1 = 42,
	color2 = 9,
	texture = 3,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_bwing_boss, "reb_bwing_boss")
