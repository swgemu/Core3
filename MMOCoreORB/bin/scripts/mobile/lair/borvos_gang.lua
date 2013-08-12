borvos_gang = Lair:new {
	mobiles = {{"borvos_thief", 0},{"borvos_thug", 0}, {"borvos_champion", 0}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_transformer.iff"},
	lairType = "npc",
}

addLairTemplate("borvos_gang", borvos_gang)
