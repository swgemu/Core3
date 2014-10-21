rebel_detachment = Lair:new {
	mobiles = {{"rebel_resistance_separatist",2},{"rebel_resistance_anarchist",2},{"rebel_resistance_leader",1}},
	spawnLimit = 8,
	buildingsVeryEasy = {"object/tangible/lair/base/objective_banner_rebel.iff"},
	buildingsEasy = {"object/tangible/lair/base/objective_banner_rebel.iff"},
	buildingsMedium = {"object/tangible/lair/base/objective_banner_rebel.iff"},
	buildingsHard = {"object/tangible/lair/base/objective_banner_rebel.iff"},
	buildingsVeryHard = {"object/tangible/lair/base/objective_banner_rebel.iff"},
	faction = "rebel",
	mobType = "npc"
}

addLairTemplate("rebel_detachment", rebel_detachment)
