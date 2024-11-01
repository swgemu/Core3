lambdashuttle_troop_transport_ace = ShipAgent:new {
	template = "lambdashuttle_tier4",
	pilotTemplate = "bomber_tier4",
	shipType = "bomber",

	experience = 8192,

	lootChance = 0.35,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 465,
	maxCredits = 900,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -136,
	rebelFactionReward = 68,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(lambdashuttle_troop_transport_ace, "lambdashuttle_troop_transport_ace")
