anthropology_collector = ShipAgent:new {
	template = "z95_tier3",
	pilotTemplate = "light_fighter_light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_story_dantooine_anthro",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},

	color1 = 3,
	color2 = 0,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(anthropology_collector, "anthropology_collector")
