reb_gunboat_tier5 = ShipAgent:new {
	template = "rebel_gunboat_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "fighter",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_rebel_tier5",

	minCredits = 525,
	maxCredits = 1075,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 192,
	rebelFactionReward = -383,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_gunboat_tier5, "reb_gunboat_tier5")
