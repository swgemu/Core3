rebel_command_vessel_weak_tier2 = ShipAgent:new {
	template = "ykl37r_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 1,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "merchant", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 26,
	rebelFactionReward = -51,

	color1 = 59,
	color2 = 10,
	texture = 1,
	appearance = "rebel_pilot",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_command_vessel_weak_tier2, "rebel_command_vessel_weak_tier2")
