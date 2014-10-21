specops_base = Lair:new {
	mobiles = {{"specops_trooper",1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_transformer.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_transformer.iff"},
	faction = "rebel",
	mobType = "npc"
}

addLairTemplate("specops_base", specops_base)
