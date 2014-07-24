dathomir_nightsister_elder_enclave_neutral_large_theater = Lair:new {
	mobiles = {
		{"nightsister_elder",1},
		{"nightsister_protector",2},
		{"nightsister_sentinel",4},
		{"nightsister_initiate",4}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/dathomir_nightsisterpatrol_large1.iff","object/building/poi/dathomir_nightsisterpatrol_large2.iff"},
	buildingsEasy = {"object/building/poi/dathomir_nightsisterpatrol_large1.iff","object/building/poi/dathomir_nightsisterpatrol_large2.iff"},
	buildingsMedium = {"object/building/poi/dathomir_nightsisterpatrol_large1.iff","object/building/poi/dathomir_nightsisterpatrol_large2.iff"},
	buildingsHard = {"object/building/poi/dathomir_nightsisterpatrol_large1.iff","object/building/poi/dathomir_nightsisterpatrol_large2.iff"},
	buildingsVeryHard = {"object/building/poi/dathomir_nightsisterpatrol_large1.iff","object/building/poi/dathomir_nightsisterpatrol_large2.iff"},
	buildingType = "theater"
}

addLairTemplate("dathomir_nightsister_elder_enclave_neutral_large_theater", dathomir_nightsister_elder_enclave_neutral_large_theater)
