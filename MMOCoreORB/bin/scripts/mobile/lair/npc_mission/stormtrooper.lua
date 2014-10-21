stormtrooper = Lair:new {
	mobiles = {{"stormtrooper",2},{"stormtrooper_medic",1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_transformer.iff"},
	faction = "imperial",
	mobType = "npc"
}

addLairTemplate("stormtrooper", stormtrooper)
