global_rebel_base3_rebel_large_theater = Lair:new {
	mobiles = {
		{"rebel_sergeant",2},
		{"rebel_sergeant_major",1},
		{"rebel_corporal",2},
		{"rebel_trooper",3}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsEasy = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsMedium = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsHard = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsVeryHard = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingType = "theater"
}

addLairTemplate("global_rebel_base3_rebel_large_theater", global_rebel_base3_rebel_large_theater)
