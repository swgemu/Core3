assaultship = ShipAgent:new {
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
	enemyFactions = {"imperial", "blacksun"},
	imperialFactionReward = 7,
	rebelFactionReward = -13,
	appearance = "rebel_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
	tauntAggressiveness = 0.05,
}

ShipAgentTemplates:addShipAgentTemplate(assaultship, "assaultship")
