rebel_command_vessel_tier4 = ShipAgent:new {
	template = "rebel_gunboat_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "bomber",

	experience = 13107.2,

	lootChance = 0.56,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 465,
	maxCredits = 950,

	aggressive = 1,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "merchant", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 109,
	rebelFactionReward = -218,
	appearance = "rebel_pilot",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_command_vessel_tier4, "rebel_command_vessel_tier4")
