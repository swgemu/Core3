rogue_imperial_shuttle_tier4 = ShipAgent:new {
	template = "lambdashuttle_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "bomber",

	experience = 8192,

	lootChance = 0.35,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 1,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "merchant"},
	enemyFactions = {"imperial", "rebel", "pirate", "hutt"},
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,

	pvpBitmask = ATTACKABLE,
	shipBitmask = NONE,
	optionsBitmask = AIENABLED,

	customShipAiMap = "",

	conversationTemplate = "",
	conversationMobile = "",
	conversationMessage = "", --Too Far Message
}

ShipAgentTemplates:addShipAgentTemplate(rogue_imperial_shuttle_tier4, "rogue_imperial_shuttle_tier4")
