anthropology_professor_boss = ShipAgent:new {
	template = "z95_tier4",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_story_dantooine_anthro",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},

	color1 = 3,
	color2 = 0,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(anthropology_professor_boss, "anthropology_professor_boss")
