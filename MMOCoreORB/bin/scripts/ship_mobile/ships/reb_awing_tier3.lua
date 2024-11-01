reb_awing_tier3 = ShipAgent:new {
	template = "awing_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 12,
	rebelFactionReward = -23,

	color1 = 59,
	color2 = 59,
	texture = 5,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_awing_tier3, "reb_awing_tier3")
