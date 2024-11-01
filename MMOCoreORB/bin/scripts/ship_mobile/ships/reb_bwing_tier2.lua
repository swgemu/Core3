reb_bwing_tier2 = ShipAgent:new {
	template = "bwing_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "fighter",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 6,
	rebelFactionReward = -12,

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

ShipAgentTemplates:addShipAgentTemplate(reb_bwing_tier2, "reb_bwing_tier2")
