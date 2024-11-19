rogue_imperial_tiebomber_tier4 = ShipAgent:new {
	template = "tiebomber_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "bomber",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 260,
	maxCredits = 575,

	aggressive = 1,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "merchant"},
	enemyFactions = {"imperial", "rebel", "pirate", "hutt"},
	appearance = "civilian",

	tauntType = "generic",
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

ShipAgentTemplates:addShipAgentTemplate(rogue_imperial_tiebomber_tier4, "rogue_imperial_tiebomber_tier4")
