mauler_gang = Lair:new {
	mobiles = {
		{"mauler", 1},
		{"mauler_acolyte", 1},
		{"mauler_apprentice", 1},
		{"mauler_master", 1}
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

addLairTemplate("mauler_gang", mauler_gang)
