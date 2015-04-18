global_imperial_stormtrooper_camp_imperial_medium_theater = Lair:new {
	mobiles = {
		{"stormtrooper",2},
		{"stormtrooper_rifleman",1},
		{"stormtrooper_bombardier",2}
	},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingsEasy = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingsMedium = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingsHard = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	buildingsVeryHard = {"object/building/poi/lok_imperial_medium4.iff","object/building/poi/lok_imperial_medium5.iff"},
	missionBuilding = "object/tangible/lair/base/objective_banner_imperial.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("global_imperial_stormtrooper_camp_imperial_medium_theater", global_imperial_stormtrooper_camp_imperial_medium_theater)
