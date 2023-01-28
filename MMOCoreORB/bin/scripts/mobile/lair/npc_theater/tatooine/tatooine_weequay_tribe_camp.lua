tatooine_weequay_tribe_camp = Lair:new {
	mobiles = {
		{"weequay_thug",1},
		{"weequay_zealot",1}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/tatooine_weequayzealots_medium.iff", "object/building/poi/tatooine_weequayzealots_medium2.iff"},
	buildingsEasy = {"object/building/poi/tatooine_weequayzealots_medium.iff", "object/building/poi/tatooine_weequayzealots_medium2.iff"},
	buildingsMedium = {"object/building/poi/tatooine_weequayzealots_medium.iff", "object/building/poi/tatooine_weequayzealots_medium2.iff"},
	buildingsHard = {"object/building/poi/tatooine_weequayzealots_medium.iff", "object/building/poi/tatooine_weequayzealots_medium2.iff"},
	buildingsVeryHard = {"object/building/poi/tatooine_weequayzealots_medium.iff", "object/building/poi/tatooine_weequayzealots_medium2.iff"},
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("tatooine_weequay_tribe_camp", tatooine_weequay_tribe_camp)
