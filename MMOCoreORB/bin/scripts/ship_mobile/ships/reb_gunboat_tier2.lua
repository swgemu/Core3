reb_gunboat_tier2 = ShipAgent:new {
	template = "rebel_gunboat_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "fighter",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 170,
	maxCredits = 368,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 20,
	rebelFactionReward = -40,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_gunboat_tier2, "reb_gunboat_tier2")
