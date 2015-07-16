corellia_corsec_camp_neutral_medium_theater = Lair:new {
	mobiles = {{"corsec_lieutenant",1},{"corsec_master_sergeant",1}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	buildingsEasy = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	buildingsMedium = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	buildingsHard = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	buildingsVeryHard = {"object/building/poi/anywhere_misc_camp_small_1.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_node.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("corellia_corsec_camp_neutral_medium_theater", corellia_corsec_camp_neutral_medium_theater)
