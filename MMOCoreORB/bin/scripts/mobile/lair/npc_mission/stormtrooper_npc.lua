stormtrooper_npc = Lair:new {
	mobiles = {{"stormtrooper_bombardier",1},{"stormtrooper_rifleman",1},{"stormtrooper_sniper",1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_generator.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_generator.iff"},
	faction = "imperial",
	mobType = "npc"
}

addLairTemplate("stormtrooper_npc", stormtrooper_npc)
