velocity_merc_heavy_fighter_tier1 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "fighter",

	experience = 120,

	lootChance = 0.204,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 1,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "merchant"},
	enemyFactions = {"imperial", "pirate"},

	color1 = 5,
	color2 = 42,
	texture = 1,
	appearance = "velocity_pilots",

	tauntType = "generic_low",
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

ShipAgentTemplates:addShipAgentTemplate(velocity_merc_heavy_fighter_tier1, "velocity_merc_heavy_fighter_tier1")
