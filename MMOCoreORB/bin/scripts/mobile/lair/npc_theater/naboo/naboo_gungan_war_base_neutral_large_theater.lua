naboo_gungan_war_base_neutral_large_theater = Lair:new {
	mobiles = {
		{"gungan_general", 1},
		{"gungan_leader", 1},
		{"gungan_falumpaset", 1},
	},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	buildingsEasy = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	buildingsMedium = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	buildingsHard = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	buildingsVeryHard = {"object/building/poi/naboo_gungwar_large1.iff","object/building/poi/naboo_gungtrad_large1.iff","object/building/poi/naboo_gungtrad_large2.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_node.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("naboo_gungan_war_base_neutral_large_theater", naboo_gungan_war_base_neutral_large_theater)
