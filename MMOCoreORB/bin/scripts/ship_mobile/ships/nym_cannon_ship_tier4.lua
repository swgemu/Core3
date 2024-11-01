nym_cannon_ship_tier4 = ShipAgent:new {
	template = "hutt_heavy_s02_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "bomber",

	experience = 4259.84,

	lootChance = 0.182,
	lootRolls = 1,
	lootTable = "space_nym_tier4",

	minCredits = 280,
	maxCredits = 650,

	aggressive = 0,

	spaceFaction = "nym",
	alliedFactions = {"rebel", "nym"},
	enemyFactions = {"imperial", "merchant", "corsair", "blacksun", "corsec", "rsf", "pirate"},

	color1 = 36,
	color2 = 31,
	texture = 4,
	questLoot = "corellia_privateer_15",
	appearance = "nym",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_cannon_ship_tier4, "nym_cannon_ship_tier4")
