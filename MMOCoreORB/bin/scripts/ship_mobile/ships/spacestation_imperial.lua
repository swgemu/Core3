spacestation_imperial = ShipAgent:new {
	template = "spacestation_imperial",
	shipType = "capital",

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier1",

	minCredits = 791,
	maxCredits = 1300,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -100,
	rebelFactionReward = 250,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,

	pvpBitmask = NONE,
	shipBitmask = NONE,
	optionsBitmask = AIENABLED + INVULNERABLE,

	customShipAiMap = "spaceStations",

	conversationTemplate = "spacestation_imperial_convotemplate",
	conversationMobile = "object/mobile/shared_space_comm_imperial_officer_01.iff",
	conversationMessage = "@conversation/pvp_station_imperial:s_48f82131", -- Too Far Message
}

ShipAgentTemplates:addShipAgentTemplate(spacestation_imperial, "spacestation_imperial")
