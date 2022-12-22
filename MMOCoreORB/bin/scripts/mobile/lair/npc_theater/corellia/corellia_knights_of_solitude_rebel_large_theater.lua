corellia_knights_of_solitude_rebel_large_theater = Lair:new {
	mobiles = {{"eye_of_solitude",1},{"foot_of_solitude",1},{"hand_of_solitude",1},{"mind_of_solitude",1},{"will_of_solitude",1}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_solitude_small4.iff"},
	buildingsEasy = {"object/building/poi/corellia_solitude_small4.iff"},
	buildingsMedium = {"object/building/poi/corellia_solitude_medium3.iff"},
	buildingsHard = {"object/building/poi/corellia_solitude_large1.iff","object/building/poi/corellia_solitude_large2.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_solitude_large1.iff","object/building/poi/corellia_solitude_large2.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_node.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("corellia_knights_of_solitude_rebel_large_theater", corellia_knights_of_solitude_rebel_large_theater)
