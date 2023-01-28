tatooine_jabba_camp = Lair:new {
	mobiles = {
		{"jabba_enforcer",1},
		{"jabba_swooper",1},
		{"jabba_assassin",1}
	},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/tatooine_hutt_assassin_camp_medium1.iff","object/building/poi/tatooine_hutt_assassin_camp_medium2.iff"},
	buildingsEasy = {"object/building/poi/tatooine_hutt_assassin_camp_medium1.iff","object/building/poi/tatooine_hutt_assassin_camp_medium2.iff"},
	buildingsMedium = {"object/building/poi/tatooine_hutt_assassin_camp_medium1.iff","object/building/poi/tatooine_hutt_assassin_camp_medium2.iff"},
	buildingsHard = {"object/building/poi/tatooine_hutt_assassin_camp_medium1.iff","object/building/poi/tatooine_hutt_assassin_camp_medium2.iff"},
	buildingsVeryHard = {"object/building/poi/tatooine_hutt_assassin_camp_medium1.iff","object/building/poi/tatooine_hutt_assassin_camp_medium2.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_generator.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("tatooine_jabba_camp", tatooine_jabba_camp)
