general_breckon_shuttle_tier4 = ShipAgent:new {
	template = "lambdashuttle_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "transport",

	experience = 8192,

	lootChance = 0.35,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(general_breckon_shuttle_tier4, "general_breckon_shuttle_tier4")
