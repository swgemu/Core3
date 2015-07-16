corellia_selonian_outpost_neutral_large_theater = Lair:new {
	mobiles = {{"selonian_raider",1},{"selonian_warrior",1},{"selonian_captain",1}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_selonian_rebel_large1.iff","object/building/poi/corellia_selonian_rebel_large2.iff"},
	buildingsEasy = {"object/building/poi/corellia_selonian_rebel_large1.iff","object/building/poi/corellia_selonian_rebel_large2.iff"},
	buildingsMedium = {"object/building/poi/corellia_selonian_rebel_large1.iff","object/building/poi/corellia_selonian_rebel_large2.iff"},
	buildingsHard = {"object/building/poi/corellia_selonian_rebel_large1.iff","object/building/poi/corellia_selonian_rebel_large2.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_selonian_rebel_large1.iff","object/building/poi/corellia_selonian_rebel_large2.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_generator.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("corellia_selonian_outpost_neutral_large_theater", corellia_selonian_outpost_neutral_large_theater)
