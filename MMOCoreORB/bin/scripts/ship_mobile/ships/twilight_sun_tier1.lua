twilight_sun_tier1 = ShipAgent:new {
	template = "rebel_gunboat_tier1",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "rebel",
	alliedFactions = {"rebel"},
	enemyFactions = {"imperial", "blacksun", "pirate", "hutt"},
	imperialFactionReward = 4,
	rebelFactionReward = -8,
	appearance = "rebel_officer",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(twilight_sun_tier1, "twilight_sun_tier1")
