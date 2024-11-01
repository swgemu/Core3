tier_3_1_a_spy = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -51,
	rebelFactionReward = 26,

	color1 = 22,
	color2 = 36,
	texture = 0,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tier_3_1_a_spy, "tier_3_1_a_spy")
