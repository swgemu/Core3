neja_bertolo_tier5 = ShipAgent:new {
	template = "awing_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6039.8,

	lootChance = 0.117,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 350,
	maxCredits = 750,

	aggressive = 1,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "merchant"},
	enemyFactions = {"imperial", "pirate"},

	color1 = 5,
	color2 = 42,
	texture = 1,
	appearance = "neja_bertolo",

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

ShipAgentTemplates:addShipAgentTemplate(neja_bertolo_tier5, "neja_bertolo_tier5")
