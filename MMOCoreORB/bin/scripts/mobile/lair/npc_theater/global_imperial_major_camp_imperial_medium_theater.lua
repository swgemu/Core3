global_imperial_major_camp_imperial_medium_theater = Lair:new {
	mobiles = {
		{"imperial_major",1},
		{"imperial_first_lieutenant",2},
		{"imperial_sergeant",2},
		{"imperial_trooper",3}
	},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingsEasy = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingsMedium = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingsHard = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingsVeryHard = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingType = "theater"
}

addLairTemplate("global_imperial_major_camp_imperial_medium_theater", global_imperial_major_camp_imperial_medium_theater)
