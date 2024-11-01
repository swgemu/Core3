reb_z95_tier4 = ShipAgent:new {
	template = "z95_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 27,
	rebelFactionReward = -54,

	color1 = 58,
	color2 = 10,
	texture = 3,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_z95_tier4, "reb_z95_tier4")
