spynet_operative_spy = ShipAgent:new {
	template = "blacksun_light_s03_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "spynet",

	color1 = 48,
	color2 = 49,
	texture = 1,
	appearance = "bothan_spynet_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(spynet_operative_spy, "spynet_operative_spy")
