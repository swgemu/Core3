po_mcannon_tier2 = ShipAgent:new {
	template = "blacksun_medium_s01_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt"},

	color1 = 5,
	color2 = 42,
	texture = 1,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(po_mcannon_tier2, "po_mcannon_tier2")
