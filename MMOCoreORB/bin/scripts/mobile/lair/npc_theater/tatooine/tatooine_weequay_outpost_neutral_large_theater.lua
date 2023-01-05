tatooine_weequay_outpost_neutral_large_theater = Lair:new {
	mobiles = {
		{"weequay_champion",1},
		{"weequay_soldier",1},
		{"weequay_thug",1},
		{"weequay_zealot",1}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/tatooine_weequayzealots_large1.iff","object/building/poi/tatooine_weequayzealots_large2.iff"},
	buildingsEasy = {"object/building/poi/tatooine_weequayzealots_large1.iff","object/building/poi/tatooine_weequayzealots_large2.iff"},
	buildingsMedium = {"object/building/poi/tatooine_weequayzealots_large1.iff","object/building/poi/tatooine_weequayzealots_large2.iff"},
	buildingsHard = {"object/building/poi/tatooine_weequayzealots_large1.iff","object/building/poi/tatooine_weequayzealots_large2.iff"},
	buildingsVeryHard = {"object/building/poi/tatooine_weequayzealots_large1.iff","object/building/poi/tatooine_weequayzealots_large2.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_transformer.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("tatooine_weequay_outpost_neutral_large_theater", tatooine_weequay_outpost_neutral_large_theater)
