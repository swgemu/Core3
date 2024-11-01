rebel_command_shuttle_tier4 = ShipAgent:new {
	template = "ykl37r_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "fighter",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 400,
	maxCredits = 800,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "merchant", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 55,
	rebelFactionReward = -109,

	color1 = 59,
	color2 = 10,
	texture = 1,
	questLoot = "stolen_data",
	appearance = "rebel_pilot",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_command_shuttle_tier4, "rebel_command_shuttle_tier4")
