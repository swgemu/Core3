coynite_merc_captain_tier3 = ShipAgent:new {
	template = "hutt_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "fighter",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial"},

	color1 = 5,
	color2 = 42,
	texture = 1,
	questLoot = "corellia_imperial_tier4_inspect3",
	appearance = "coynite_officer",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(coynite_merc_captain_tier3, "coynite_merc_captain_tier3")
