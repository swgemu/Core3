rori_mauler_conclave_neutral_large_theater = Lair:new {
	mobiles = {
		{"mauler_lord",1},
		{"mauler",2},
		{"mauler_acolyte",2},
		{"mauler_apprentice",2},
		{"mauler_veermok",1}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/naboo_mauler_large1.iff","object/building/poi/naboo_mauler_large2.iff"},
	buildingsEasy = {"object/building/poi/naboo_mauler_large1.iff","object/building/poi/naboo_mauler_large2.iff"},
	buildingsMedium = {"object/building/poi/naboo_mauler_large1.iff","object/building/poi/naboo_mauler_large2.iff"},
	buildingsHard = {"object/building/poi/naboo_mauler_large1.iff","object/building/poi/naboo_mauler_large2.iff"},
	buildingsVeryHard = {"object/building/poi/naboo_mauler_large1.iff","object/building/poi/naboo_mauler_large2.iff"},
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("rori_mauler_conclave_neutral_large_theater", rori_mauler_conclave_neutral_large_theater)
