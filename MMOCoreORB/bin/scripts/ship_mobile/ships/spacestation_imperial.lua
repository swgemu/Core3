spacestation_imperial = ShipAgent:new {
	template = "spacestation_imperial",
	shipType = "capital",

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier1",

	minCredits = 791,
	maxCredits = 1300,

	aggressive = 0,

	spaceFaction = "station",
	imperialFactionReward = -100,
	rebelFactionReward = 250,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(spacestation_imperial, "spacestation_imperial")
