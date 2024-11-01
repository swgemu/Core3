reb_yavinspy_tier4 = ShipAgent:new {
	template = "awing_tier4",
	pilotTemplate = "light_fighter_tier4",
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
	imperialFactionReward = 25,
	rebelFactionReward = -49,

	color1 = 59,
	color2 = 59,
	texture = 5,
	questLoot = "joint_operations_plan",
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_yavinspy_tier4, "reb_yavinspy_tier4")
