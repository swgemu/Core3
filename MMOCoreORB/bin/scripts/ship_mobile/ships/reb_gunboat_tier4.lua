reb_gunboat_tier4 = ShipAgent:new {
	template = "rebel_gunboat_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "fighter",

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
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_gunboat_tier4, "reb_gunboat_tier4")
