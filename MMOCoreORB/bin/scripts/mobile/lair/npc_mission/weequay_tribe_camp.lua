weequay_tribe_camp = Lair:new {
	mobiles = {{"weequay_champion", 0},{"weequay_soldier", 0},{"weequay_thug", 0},{"weequay_zealot", 0}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	lairType = "npc",
}

addLairTemplate("weequay_tribe_camp", weequay_tribe_camp)
