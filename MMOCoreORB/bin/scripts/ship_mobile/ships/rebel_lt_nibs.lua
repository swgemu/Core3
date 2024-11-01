rebel_lt_nibs = ShipAgent:new {
	template = "awing_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "merchant", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 4,
	rebelFactionReward = -7,

	color1 = 59,
	color2 = 59,
	texture = 5,
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_lt_nibs, "rebel_lt_nibs")
