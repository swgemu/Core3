shinss_yacht_tier3 = ShipAgent:new {
	template = "lambdashuttle_tier3",
	pilotTemplate = "bomber_tier3",
	shipType = "transport",

	experience = 3200,

	lootChance = 0.375,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 58,
	maxCredits = 736,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "merchant"},
	enemyFactions = {"imperial", "rebel", "hutt", "pirate"},
	questLoot = "shinss_personal_logs",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(shinss_yacht_tier3, "shinss_yacht_tier3")
