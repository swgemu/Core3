dathomir_prison_shuttle_tier4 = ShipAgent:new {
	template = "decimator_tier4",
	pilotTemplate = "heavy_tier1",
	shipType = "bomber",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 400,
	maxCredits = 800,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"corsec"},
	imperialFactionReward = -218,
	rebelFactionReward = 109,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dathomir_prison_shuttle_tier4, "dathomir_prison_shuttle_tier4")
