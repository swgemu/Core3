escort_tie_basic_tier4 = ShipAgent:new {
	template = "tiefighter_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -54,
	rebelFactionReward = 27,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(escort_tie_basic_tier4, "escort_tie_basic_tier4")
