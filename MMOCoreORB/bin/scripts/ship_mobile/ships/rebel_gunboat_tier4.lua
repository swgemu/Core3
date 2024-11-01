rebel_gunboat_tier4 = ShipAgent:new {
	template = "rebel_gunboat_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "bomber",

	experience = 13107.2,

	lootChance = 0.56,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 465,
	maxCredits = 950,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 109,
	rebelFactionReward = -218,
	appearance = "rebel_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_gunboat_tier4, "rebel_gunboat_tier4")
