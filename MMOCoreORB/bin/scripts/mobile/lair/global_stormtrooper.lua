global_stormtrooper = Lair:new {
	mobiles = {{"stormtrooper", 25}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_banner_imperial.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_banner_imperial.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_banner_imperial.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_banner_imperial.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_banner_imperial.iff"},
	faction = "imperial"
}

addLairTemplate("global_stormtrooper", global_stormtrooper)
