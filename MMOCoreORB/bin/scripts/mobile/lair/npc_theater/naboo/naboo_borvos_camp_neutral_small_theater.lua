naboo_borvos_camp_neutral_small_theater = Lair:new {
	mobiles = {{"borvos_bruiser",1},{"borvos_soldier",1},{"borvos_mercenary",1}},
	spawnLimit = 9,
	buildingsVeryEasy = {"object/building/poi/naboo_borvos_medium.iff"},
	buildingsEasy = {"object/building/poi/naboo_borvos_medium.iff"},
	buildingsMedium = {"object/building/poi/naboo_borvos_medium.iff"},
	buildingsHard = {"object/building/poi/naboo_borvos_medium.iff"},
	buildingsVeryHard = {"object/building/poi/naboo_borvos_medium.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_generator.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("naboo_borvos_camp_neutral_small_theater", naboo_borvos_camp_neutral_small_theater)
