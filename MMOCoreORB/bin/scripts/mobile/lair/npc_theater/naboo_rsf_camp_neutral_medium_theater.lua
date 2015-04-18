naboo_rsf_camp_neutral_medium_theater = Lair:new {
	mobiles = {{"rsf_commando",1},{"rsf_security_guard",1},{"rsf_security_officer",1}},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/naboo_police_medium.iff","object/building/poi/naboo_politic_medium.iff"},
	buildingsEasy = {"object/building/poi/naboo_police_medium.iff","object/building/poi/naboo_politic_medium.iff"},
	buildingsMedium = {"object/building/poi/naboo_police_medium.iff","object/building/poi/naboo_politic_medium.iff"},
	buildingsHard = {"object/building/poi/naboo_police_medium.iff","object/building/poi/naboo_politic_medium.iff"},
	buildingsVeryHard = {"object/building/poi/naboo_police_medium.iff","object/building/poi/naboo_politic_medium.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_transformer.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("naboo_rsf_camp_neutral_medium_theater", naboo_rsf_camp_neutral_medium_theater)
