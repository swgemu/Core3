borvos_gang = Lair:new {
	mobiles = {{"borvos_thief", 1},{"borvos_thug", 1}, {"borvos_champion", 1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_transformer.iff"},
	mobType = "npc",
}

addLairTemplate("borvos_gang", borvos_gang)
