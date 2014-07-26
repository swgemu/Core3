global_rebel_specforce_base_rebel_large_theater = Lair:new {
	mobiles = {
		{"rebel_specforce_captain",1},
		{"rebel_specforce_sergeant",2},
		{"rebel_specforce_urban_guerrilla",3},
		{"senior_specforce_urban_guerrilla",2}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsEasy = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsMedium = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsHard = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsVeryHard = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingType = "theater"
}

addLairTemplate("global_rebel_specforce_base_rebel_large_theater", global_rebel_specforce_base_rebel_large_theater)
