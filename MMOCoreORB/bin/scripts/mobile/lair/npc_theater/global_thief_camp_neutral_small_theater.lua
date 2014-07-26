global_thief_camp_neutral_small_theater = Lair:new {
	mobiles = {
		{"master_thief",1},
		{"thief",3}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_meatlump_small1.iff","object/building/poi/corellia_meatlump_small2.iff","object/building/poi/corellia_meatlump_small3.iff"},
	buildingsEasy = {"object/building/poi/corellia_meatlump_small1.iff","object/building/poi/corellia_meatlump_small2.iff","object/building/poi/corellia_meatlump_small3.iff"},
	buildingsMedium = {"object/building/poi/corellia_meatlump_small1.iff","object/building/poi/corellia_meatlump_small2.iff","object/building/poi/corellia_meatlump_small3.iff"},
	buildingsHard = {"object/building/poi/corellia_meatlump_small1.iff","object/building/poi/corellia_meatlump_small2.iff","object/building/poi/corellia_meatlump_small3.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_meatlump_small1.iff","object/building/poi/corellia_meatlump_small2.iff","object/building/poi/corellia_meatlump_small3.iff"},
	buildingType = "theater"
}

addLairTemplate("global_thief_camp_neutral_small_theater", global_thief_camp_neutral_small_theater)
