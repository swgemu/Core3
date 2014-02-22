mauler_gang = Lair:new {
	mobiles = {{"mauler_acolyte", 0}, {"mauler_apprentice", 0}, {"mauler", 0}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_node.iff"},
	lairType = "npc",
}

addLairTemplate("mauler_gang", mauler_gang)
