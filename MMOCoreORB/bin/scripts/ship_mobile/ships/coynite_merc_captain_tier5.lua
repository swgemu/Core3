coynite_merc_captain_tier5 = ShipAgent:new {
	template = "hutt_heavy_s01_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "fighter",

	experience = 8724.15,

	lootChance = 0.169,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 465,
	maxCredits = 925,

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

ShipAgentTemplates:addShipAgentTemplate(coynite_merc_captain_tier5, "coynite_merc_captain_tier5")
