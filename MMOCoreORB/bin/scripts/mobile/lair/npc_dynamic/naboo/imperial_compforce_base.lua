imperial_compforce_base = Lair:new {
	mobiles = {
		{"compforce_trooper", 3},
		{"veteran_compforce_trooper", 1},
	},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/hq/imperial_med.iff"},
	buildingsEasy = {"object/building/poi/hq/imperial_med.iff"},
	buildingsMedium = {"object/building/poi/hq/imperial_med.iff"},
	buildingsHard = {"object/building/poi/hq/imperial_med.iff"},
	buildingsVeryHard = {"object/building/poi/hq/imperial_med.iff"},
	missionBuilding = "object/tangible/lair/base/objective_banner_imperial.iff",
	mobType = "npc",
	buildingType = "theater",
	faction = "imperial"
}

addLairTemplate("imperial_compforce_base", imperial_compforce_base)
