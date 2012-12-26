rebel = Lair:new {
	mobiles = {{"rebel_commando", 25}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_generator.iff"},
	faction = "rebel",
}

addLairTemplate("rebel", rebel)
