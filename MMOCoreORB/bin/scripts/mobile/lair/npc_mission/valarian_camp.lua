valarian_camp = Lair:new {
	mobiles = {{"valarian_henchman", 1}, {"valarian_scout", 1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_banner_generic_2.iff"},
	mobType = "npc",
}

addLairTemplate("valarian_camp", valarian_camp)
