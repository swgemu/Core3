valarian_swooper_camp = Lair:new {
	mobiles = {{"valarian_swooper_leader",1},{"valarian_swooper",2}},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/tatooine_swoop_medium.iff","object/building/poi/tatooine_swoop_medium2.iff"},
	buildingsEasy = {"object/building/poi/tatooine_swoop_medium.iff","object/building/poi/tatooine_swoop_medium2.iff"},
	buildingsMedium = {"object/building/poi/tatooine_swoop_medium.iff","object/building/poi/tatooine_swoop_medium2.iff"},
	buildingsHard = {"object/building/poi/tatooine_swoop_medium.iff","object/building/poi/tatooine_swoop_medium2.iff"},
	buildingsVeryHard = {"object/building/poi/tatooine_swoop_medium.iff","object/building/poi/tatooine_swoop_medium2.iff"},
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("valarian_swooper_camp", valarian_swooper_camp)
