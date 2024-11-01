junk_dealer_overseer = ShipAgent:new {
	template = "hutt_heavy_s01_tier4",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "fighter",

	experience = 4259.84,

	lootChance = 0.182,
	lootRolls = 1,
	lootTable = "space_story_dantooine_junk",

	minCredits = 280,
	maxCredits = 650,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"civilian", "rebel", "imperial", "merchant"},
	enemyFactions = {"pirate", "blacksun"},

	color1 = 20,
	color2 = 51,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(junk_dealer_overseer, "junk_dealer_overseer")
