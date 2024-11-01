rebel_lt_asperago = ShipAgent:new {
	template = "ywing_tier2",
	pilotTemplate = "bomber_tier3",
	shipType = "fighter",

	experience = 420,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "merchant", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 4,
	rebelFactionReward = -8,
	color2 = 42,
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_lt_asperago, "rebel_lt_asperago")
