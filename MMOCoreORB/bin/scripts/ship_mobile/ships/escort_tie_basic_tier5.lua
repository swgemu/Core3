escort_tie_basic_tier5 = ShipAgent:new {
	template = "tiefighter_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_imperial_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -95,
	rebelFactionReward = 48,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(escort_tie_basic_tier5, "escort_tie_basic_tier5")
