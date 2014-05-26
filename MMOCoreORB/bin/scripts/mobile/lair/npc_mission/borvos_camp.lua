borvos_camp = Lair:new {
	mobiles = {{"borvos_bruiser", 1},{"borvos_mercenary", 1},{"borvos_soldier", 1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	mobType = "npc",
}

addLairTemplate("borvos_camp", borvos_camp)
