reb_awing_boss = ShipAgent:new {
	template = "awing_tier4",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 21,
	rebelFactionReward = -42,

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

ShipAgentTemplates:addShipAgentTemplate(reb_awing_boss, "reb_awing_boss")
