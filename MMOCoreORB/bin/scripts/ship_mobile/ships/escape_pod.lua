escape_pod = ShipAgent:new {
	template = "escape_pod_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 0,

	spaceFaction = "civilian",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(escape_pod, "escape_pod")
