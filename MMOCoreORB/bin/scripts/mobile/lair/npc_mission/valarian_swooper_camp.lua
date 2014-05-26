valarian_swooper_camp = Lair:new {
	mobiles = {{"valarian_swooper_leader", 1},{"valarian_swooper", 1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_generator.iff"},
	mobType = "npc",
}

addLairTemplate("valarian_swooper_camp", valarian_swooper_camp)
