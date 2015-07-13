naboo_gungan_military_base_neutral_large_theater = Lair:new {
	mobiles = {
		{"gungan_captain", 1},
		{"gungan_grand_army_soldier", 2},
		{"gungan_bomber", 2},
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	buildingsEasy = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	buildingsMedium = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	buildingsHard = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	buildingsVeryHard = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("naboo_gungan_military_base_neutral_large_theater", naboo_gungan_military_base_neutral_large_theater)
