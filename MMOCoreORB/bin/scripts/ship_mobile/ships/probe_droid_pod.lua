probe_droid_pod = ShipAgent:new {
	template = "probe_droid_pod_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 25,

	lootChance = 0.0425,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 0,
	maxCredits = 5,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = 0,
	rebelFactionReward = 0,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(probe_droid_pod, "probe_droid_pod")
