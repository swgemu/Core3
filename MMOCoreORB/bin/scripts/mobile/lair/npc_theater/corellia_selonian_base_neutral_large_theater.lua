corellia_selonian_base_neutral_large_theater = Lair:new {
	mobiles = {{"selonian_separatist",3},{"selonian_separatist_general",1},{"selonian_separatist_soldier",3},{"selonian_separatist_recruit",3},{"selonian_separatist_captain",2}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_selonian_separatists_large1.iff","object/building/poi/corellia_selonian_separatists_large2.iff"},
	buildingsEasy = {"object/building/poi/corellia_selonian_separatists_large1.iff","object/building/poi/corellia_selonian_separatists_large2.iff"},
	buildingsMedium = {"object/building/poi/corellia_selonian_separatists_large1.iff","object/building/poi/corellia_selonian_separatists_large2.iff"},
	buildingsHard = {"object/building/poi/corellia_selonian_separatists_large1.iff","object/building/poi/corellia_selonian_separatists_large2.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_selonian_separatists_large1.iff","object/building/poi/corellia_selonian_separatists_large2.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_node.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("corellia_selonian_base_neutral_large_theater", corellia_selonian_base_neutral_large_theater)
