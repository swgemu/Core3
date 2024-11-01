bothan_spynet_fighter_tier4 = ShipAgent:new {
	template = "blacksun_medium_s01_tier4",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 260,
	maxCredits = 575,

	aggressive = 0,

	spaceFaction = "spynet",
	alliedFactions = {"spynet"},

	color1 = 30,
	color2 = 36,
	texture = 2,
	appearance = "bothan_spynet_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(bothan_spynet_fighter_tier4, "bothan_spynet_fighter_tier4")
