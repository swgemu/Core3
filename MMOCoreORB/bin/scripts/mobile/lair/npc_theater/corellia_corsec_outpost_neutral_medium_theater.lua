corellia_corsec_outpost_neutral_medium_theater = Lair:new {
	mobiles = {{"corsec_captain",1},{"corsec_lieutenant",2},{"corsec_master_sergeant",2},{"corsec_major",1},{"corsec_trooper",3}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_hidden_large1.iff"},
	buildingsEasy = {"object/building/poi/corellia_hidden_large1.iff"},
	buildingsMedium = {"object/building/poi/corellia_hidden_large1.iff"},
	buildingsHard = {"object/building/poi/corellia_hidden_large1.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_hidden_large1.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_generator.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("corellia_corsec_outpost_neutral_medium_theater", corellia_corsec_outpost_neutral_medium_theater)
