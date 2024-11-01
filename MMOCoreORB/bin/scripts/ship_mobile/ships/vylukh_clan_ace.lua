vylukh_clan_ace = ShipAgent:new {
	template = "xwing_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 110,

	lootChance = 0.187,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 55,
	maxCredits = 110,

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

ShipAgentTemplates:addShipAgentTemplate(vylukh_clan_ace, "vylukh_clan_ace")
