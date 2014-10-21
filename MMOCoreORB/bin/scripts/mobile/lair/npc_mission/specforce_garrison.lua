specforce_garrison = Lair:new {
	mobiles = {{"rebel_specforce_pathfinder",2},{"rebel_specforce_sergeant",2},{"rebel_specforce_captain",1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_node.iff"},
	faction = "rebel",
	mobType = "npc"
}

addLairTemplate("specforce_garrison", specforce_garrison)
