bothan_spynet_shuttle_tier4 = ShipAgent:new {
	template = "transport_science_tier4",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "spynet",
	appearance = "bothan_spynet_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(bothan_spynet_shuttle_tier4, "bothan_spynet_shuttle_tier4")
