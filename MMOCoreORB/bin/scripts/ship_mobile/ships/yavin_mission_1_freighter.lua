yavin_mission_1_freighter = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "fighter",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 95,
	maxCredits = 240,

	aggressive = 0,

	spaceFaction = "rebel",
	imperialFactionReward = 10,
	rebelFactionReward = -20,

	color1 = 59,
	color2 = 10,
	texture = 5,
	formationLocation = 3,
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(yavin_mission_1_freighter, "yavin_mission_1_freighter")
