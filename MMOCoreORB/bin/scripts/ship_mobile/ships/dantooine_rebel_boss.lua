dantooine_rebel_boss = ShipAgent:new {
	template = "awing_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "bomber",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel"},
	enemyFactions = {"imperial", "pirate"},
	imperialFactionReward = 25,
	rebelFactionReward = -49,

	color1 = 3,
	color2 = 59,
	texture = 5,
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_rebel_boss, "dantooine_rebel_boss")
