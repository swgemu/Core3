player_command_tie_bomber_tier2 = ShipAgent:new {
	template = "tiebomber_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "bomber",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_imperial_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -11,
	rebelFactionReward = 6,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(player_command_tie_bomber_tier2, "player_command_tie_bomber_tier2")
