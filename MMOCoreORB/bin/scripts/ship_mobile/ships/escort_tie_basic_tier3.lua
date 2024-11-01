escort_tie_basic_tier3 = ShipAgent:new {
	template = "tiefighter_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -25,
	rebelFactionReward = 13,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(escort_tie_basic_tier3, "escort_tie_basic_tier3")
