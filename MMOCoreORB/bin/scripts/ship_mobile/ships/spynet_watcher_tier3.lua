spynet_watcher_tier3 = ShipAgent:new {
	template = "blacksun_light_s04_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "spynet",
	enemyFactions = {"imperial"},

	color1 = 48,
	color2 = 49,
	texture = 1,
	questLoot = "spynet_watcher_cargo",
	appearance = "bothan_spynet_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(spynet_watcher_tier3, "spynet_watcher_tier3")
