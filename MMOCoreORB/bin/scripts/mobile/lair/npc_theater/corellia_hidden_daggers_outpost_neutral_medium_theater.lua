corellia_hidden_daggers_outpost_neutral_medium_theater = Lair:new {
	mobiles = {{"hidden_daggers_extremist",1},{"hidden_daggers_lieutenant",1},{"hidden_daggers_leader",1}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_hidden_large1.iff"},
	buildingsEasy = {"object/building/poi/corellia_hidden_large1.iff"},
	buildingsMedium = {"object/building/poi/corellia_hidden_large1.iff"},
	buildingsHard = {"object/building/poi/corellia_hidden_large1.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_hidden_large1.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_transformer.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("corellia_hidden_daggers_outpost_neutral_medium_theater", corellia_hidden_daggers_outpost_neutral_medium_theater)
