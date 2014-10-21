rebel_listening_post = Lair:new {
	mobiles = {{"rebel_network_leader",1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_power_node.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_power_node.iff"},
	faction = "rebel",
	mobType = "npc"
}

addLairTemplate("rebel_listening_post", rebel_listening_post)
