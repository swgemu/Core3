reb_bwing_tier4 = ShipAgent:new {
	template = "bwing_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "fighter",

	experience = 3932.16,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 275,
	maxCredits = 600,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 33,
	rebelFactionReward = -65,

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

ShipAgentTemplates:addShipAgentTemplate(reb_bwing_tier4, "reb_bwing_tier4")
