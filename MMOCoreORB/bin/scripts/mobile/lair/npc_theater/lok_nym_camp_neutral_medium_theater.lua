lok_nym_camp_neutral_medium_theater = Lair:new {
	mobiles = {{"nym_pirate_weak",1},{"nym_brawler",1},{"nym_surveyor",1}},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/lok_nymshenchman_medium.iff","object/building/poi/lok_nymshenchman_medium2.iff","object/building/poi/lok_nymshenchman_medium3.iff"},
	buildingsEasy = {"object/building/poi/lok_nymshenchman_medium.iff","object/building/poi/lok_nymshenchman_medium2.iff","object/building/poi/lok_nymshenchman_medium3.iff"},
	buildingsMedium = {"object/building/poi/lok_nymshenchman_medium.iff","object/building/poi/lok_nymshenchman_medium2.iff","object/building/poi/lok_nymshenchman_medium3.iff"},
	buildingsHard = {"object/building/poi/lok_nymshenchman_medium.iff","object/building/poi/lok_nymshenchman_medium2.iff","object/building/poi/lok_nymshenchman_medium3.iff"},
	buildingsVeryHard = {"object/building/poi/lok_nymshenchman_medium.iff","object/building/poi/lok_nymshenchman_medium2.iff","object/building/poi/lok_nymshenchman_medium3.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_generator.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("lok_nym_camp_neutral_medium_theater", lok_nym_camp_neutral_medium_theater)
