corellia_drall_camp_neutral_medium_theater = Lair:new {
	mobiles = {{"drall_abbot",1},{"drall_chieftain",1},{"drall_guard",2},{"drall_master",2}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_drall_abbots_camp_small1.iff"},
	buildingsEasy = {"object/building/poi/corellia_drall_abbots_camp_small1.iff"},
	buildingsMedium = {"object/building/poi/corellia_drall_abbot_small1.iff","object/building/poi/corellia_drall_abbot_small2.iff"},
	buildingsHard = {"object/building/poi/corellia_drall_abbot_small1.iff","object/building/poi/corellia_drall_abbot_small2.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_drall_abbot_large1.iff","object/building/poi/corellia_drall_abbot_large2.iff"},
	buildingType = "theater"
}

addLairTemplate("corellia_drall_camp_neutral_medium_theater", corellia_drall_camp_neutral_medium_theater)
