yt1300_rebel_freighter = ShipAgent:new {
	template = "yt1300_tier4",
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
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun"},
	imperialFactionReward = 55,
	rebelFactionReward = -109,

	color1 = 40,
	color2 = 16,
	texture = 5,
	formationLocation = 3,
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(yt1300_rebel_freighter, "yt1300_rebel_freighter")
