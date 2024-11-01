vylukh_clan_ace_tier3 = ShipAgent:new {
	template = "xwing_tier3",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt"},

	color1 = 1,
	color2 = 14,
	texture = 2,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(vylukh_clan_ace_tier3, "vylukh_clan_ace_tier3")
