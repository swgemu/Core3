polard_manfred_yt1300_tier2 = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "bomber",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "merchant",
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(polard_manfred_yt1300_tier2, "polard_manfred_yt1300_tier2")
