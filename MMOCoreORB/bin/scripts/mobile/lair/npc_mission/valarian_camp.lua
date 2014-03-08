valarian_camp = Lair:new {
	mobiles = {{"valarian_henchman", 0}, {"valarian_scout", 0}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	mobType = "npc",
}

addLairTemplate("valarian_camp", valarian_camp)
