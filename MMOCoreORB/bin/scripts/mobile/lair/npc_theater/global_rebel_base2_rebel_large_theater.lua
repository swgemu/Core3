global_rebel_base2_rebel_large_theater = Lair:new {
	mobiles = {
		{"rebel_second_lieutenant",1},
		{"rebel_corporal",2},
		{"rebel_trooper",2},
		{"rebel_medic",1}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsEasy = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsMedium = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsHard = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsVeryHard = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingType = "theater"
}

addLairTemplate("global_rebel_base2_rebel_large_theater", global_rebel_base2_rebel_large_theater)
