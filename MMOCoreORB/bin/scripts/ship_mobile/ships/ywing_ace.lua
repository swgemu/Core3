ywing_ace = ShipAgent:new {
	template = "ywing_tier1",
	pilotTemplate = "bomber_tier1",
	shipType = "fighter",

	experience = 105,

	lootChance = 0.1785,
	lootRolls = 1,
	lootTable = "space_rebel_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun"},
	imperialFactionReward = 2,
	rebelFactionReward = -3,
	color2 = 42,
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
	tauntAggressiveness = 0.05,
}

ShipAgentTemplates:addShipAgentTemplate(ywing_ace, "ywing_ace")
