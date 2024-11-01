rebel_boss = ShipAgent:new {
	template = "xwing_tier2",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 4,
	rebelFactionReward = -8,

	color1 = 4,
	color2 = 4,
	texture = 3,
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_boss, "rebel_boss")
