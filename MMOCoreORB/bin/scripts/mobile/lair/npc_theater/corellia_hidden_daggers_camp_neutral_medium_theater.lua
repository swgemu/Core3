corellia_hidden_daggers_camp_neutral_medium_theater = Lair:new {
	mobiles = {{"hidden_daggers_extremist",1}, {"hidden_daggers_dissident",1},{"hidden_daggers_activist",1}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	buildingsEasy = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	buildingsMedium = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	buildingsHard = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	buildingsVeryHard = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_generator.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("corellia_hidden_daggers_camp_neutral_medium_theater", corellia_hidden_daggers_camp_neutral_medium_theater)
