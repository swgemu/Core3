mauler_gang = Lair:new {
	mobiles = {{"mauler_acolyte", 1}, {"mauler_apprentice", 1}, {"mauler", 1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_node.iff"},
	mobType = "npc",
}

addLairTemplate("mauler_gang", mauler_gang)
