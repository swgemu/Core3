tatooine_tusken_camp = Lair:new {
	mobiles = {
		{"tusken_raider", 2},
		{"tusken_commoner", 2},
		{"tusken_child", 1},
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/tatooine_tuskenbantha_medium.iff"},
	buildingsEasy = {"object/building/poi/tatooine_tuskenbantha_medium.iff"},
	buildingsMedium = {"object/building/poi/tatooine_tuskenbantha_medium.iff"},
	buildingsHard = {"object/building/poi/tatooine_tuskenbantha_medium.iff"},
	buildingsVeryHard = {"object/building/poi/tatooine_tuskenbantha_medium.iff"},
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("tatooine_tusken_camp", tatooine_tusken_camp)
