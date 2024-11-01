dath_witchblood_clan_punisher_tier5 = ShipAgent:new {
	template = "hutt_heavy_s01_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "fighter",

	experience = 8724.15,

	lootChance = 0.169,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 465,
	maxCredits = 925,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "hutt", "valarian", "rsf", "corsec"},

	color1 = 59,
	color2 = 59,
	texture = 6,
	questLoot = "witchblood_baseinfo",
	appearance = "witchblood_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dath_witchblood_clan_punisher_tier5, "dath_witchblood_clan_punisher_tier5")
