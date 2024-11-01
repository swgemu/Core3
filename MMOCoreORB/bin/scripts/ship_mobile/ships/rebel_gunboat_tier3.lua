rebel_gunboat_tier3 = ShipAgent:new {
	template = "rebel_gunboat_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "bomber",

	experience = 5120,

	lootChance = 0.6,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 94,
	maxCredits = 700,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 51,
	rebelFactionReward = -102,
	appearance = "rebel_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_gunboat_tier3, "rebel_gunboat_tier3")
