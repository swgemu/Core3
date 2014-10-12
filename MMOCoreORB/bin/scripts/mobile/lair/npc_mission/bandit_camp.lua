bandit_camp = Lair:new {
	mobiles = {{"bandit",1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_banner_generic_1.iff"},
	mobType = "npc"
}

addLairTemplate("bandit_camp", bandit_camp)
