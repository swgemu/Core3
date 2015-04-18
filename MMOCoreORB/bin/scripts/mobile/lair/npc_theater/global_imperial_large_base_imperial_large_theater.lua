global_imperial_large_base_imperial_large_theater = Lair:new {
	mobiles = {
		{"imperial_colonel",1},
		{"imperial_major",1},
		{"imperial_first_lieutenant",2},
		{"imperial_sergeant",3}
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/lok_imperial_large2.iff","object/building/poi/anywhere_imperial_base_large_1.iff"},
	buildingsEasy = {"object/building/poi/lok_imperial_large2.iff","object/building/poi/anywhere_imperial_base_large_1.iff"},
	buildingsMedium = {"object/building/poi/lok_imperial_large2.iff","object/building/poi/anywhere_imperial_base_large_1.iff"},
	buildingsHard = {"object/building/poi/lok_imperial_large2.iff","object/building/poi/anywhere_imperial_base_large_1.iff"},
	buildingsVeryHard = {"object/building/poi/lok_imperial_large2.iff","object/building/poi/anywhere_imperial_base_large_1.iff"},
	missionBuilding = "object/tangible/lair/base/objective_banner_imperial.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("global_imperial_large_base_imperial_large_theater", global_imperial_large_base_imperial_large_theater)
