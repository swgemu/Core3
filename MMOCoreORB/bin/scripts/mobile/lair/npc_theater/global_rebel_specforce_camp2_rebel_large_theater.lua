global_rebel_specforce_camp2_rebel_large_theater = Lair:new {
	mobiles = {
		{"specforce_marine",4},
		{"specforce_heavy_weapons_specialist",2},
		{"senior_specforce_heavy_weapons_specialist",1},
		{"senior_specforce_marine",1},
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsEasy = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsMedium = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsHard = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	buildingsVeryHard = {"object/building/poi/anywhere_rebel_base_large_1.iff"},
	missionBuilding = "object/tangible/lair/base/objective_banner_rebel.iff",
	mobType = "npc",
	buildingType = "theater",
	faction = "rebel"
}

addLairTemplate("global_rebel_specforce_camp2_rebel_large_theater", global_rebel_specforce_camp2_rebel_large_theater)
