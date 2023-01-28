tatooine_dune_stalker_camp = Lair:new {
	mobiles = {{"dune_stalker_leader",1},{"dune_stalker_brawler",1},{"dune_stalker_enforcer",1},{"dune_stalker_marksman",1},{"dune_stalker_scavenger",1},{"dune_stalker",1}},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/tatooine_dunestalkers_large1.iff"},
	buildingsEasy = {"object/building/poi/tatooine_dunestalkers_large1.iff"},
	buildingsMedium = {"object/building/poi/tatooine_dunestalkers_large1.iff"},
	buildingsHard = {"object/building/poi/tatooine_dunestalkers_large1.iff"},
	buildingsVeryHard = {"object/building/poi/tatooine_dunestalkers_large1.iff"},
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("tatooine_dune_stalker_camp", tatooine_dune_stalker_camp)
