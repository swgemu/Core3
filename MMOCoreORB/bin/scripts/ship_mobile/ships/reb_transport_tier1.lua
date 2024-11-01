reb_transport_tier1 = ShipAgent:new {
	template = "rebel_shuttle_tier1",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier1",

	minCredits = 4,
	maxCredits = 57,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -10,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_transport_tier1, "reb_transport_tier1")
