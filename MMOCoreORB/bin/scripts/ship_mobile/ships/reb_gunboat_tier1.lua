reb_gunboat_tier1 = ShipAgent:new {
	template = "rebel_gunboat_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_rebel_tier1",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 7,
	rebelFactionReward = -13,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_gunboat_tier1, "reb_gunboat_tier1")
