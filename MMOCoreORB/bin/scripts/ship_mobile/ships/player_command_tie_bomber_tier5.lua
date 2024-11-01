player_command_tie_bomber_tier5 = ShipAgent:new {
	template = "tiebomber_tier5",
	pilotTemplate = "bomber_tier5",
	shipType = "bomber",

	experience = 7381.98,

	lootChance = 0.143,
	lootRolls = 1,
	lootTable = "space_imperial_tier5",

	minCredits = 455,
	maxCredits = 875,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -105,
	rebelFactionReward = 53,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(player_command_tie_bomber_tier5, "player_command_tie_bomber_tier5")
