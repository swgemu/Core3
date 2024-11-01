reb_transport_tier3 = ShipAgent:new {
	template = "rebel_shuttle_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier3",

	minCredits = 58,
	maxCredits = 736,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -30,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_transport_tier3, "reb_transport_tier3")
