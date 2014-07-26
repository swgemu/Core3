global_pirate_dread_camp_neutral_large_theater = Lair:new {
	mobiles = {
		{"dread_pirate",1},
		{"pirate_armsman",2},
		{"pirate_cutthroat",2}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/tatooine_gunrunners_large1.iff","object/building/poi/tatooine_gunrunners_large2.iff","object/building/poi/naboo_gunrunners_large1.iff","object/building/poi/naboo_gunrunners_large2.iff"},
	buildingsEasy = {"object/building/poi/tatooine_gunrunners_large1.iff","object/building/poi/tatooine_gunrunners_large2.iff","object/building/poi/naboo_gunrunners_large1.iff","object/building/poi/naboo_gunrunners_large2.iff"},
	buildingsMedium = {"object/building/poi/tatooine_gunrunners_large1.iff","object/building/poi/tatooine_gunrunners_large2.iff","object/building/poi/naboo_gunrunners_large1.iff","object/building/poi/naboo_gunrunners_large2.iff"},
	buildingsHard = {"object/building/poi/tatooine_gunrunners_large1.iff","object/building/poi/tatooine_gunrunners_large2.iff","object/building/poi/naboo_gunrunners_large1.iff","object/building/poi/naboo_gunrunners_large2.iff"},
	buildingsVeryHard = {"object/building/poi/tatooine_gunrunners_large1.iff","object/building/poi/tatooine_gunrunners_large2.iff","object/building/poi/naboo_gunrunners_large1.iff","object/building/poi/naboo_gunrunners_large2.iff"},
	buildingType = "theater"
}

addLairTemplate("global_pirate_dread_camp_neutral_large_theater", global_pirate_dread_camp_neutral_large_theater)
