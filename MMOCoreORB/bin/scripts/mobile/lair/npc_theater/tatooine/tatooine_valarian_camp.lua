tatooine_valarian_camp = Lair:new {
	mobiles = {
		{"valarian_enforcer",1},
		{"valarian_thief",1},
		{"valarian_thug",1},
		{"valarian_scout",1}
	},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/tatooine_valariangang_medium.iff","object/building/poi/tatooine_valariantrader_medium.iff"},
	buildingsEasy = {"object/building/poi/tatooine_valariangang_medium.iff","object/building/poi/tatooine_valariantrader_medium.iff"},
	buildingsMedium = {"object/building/poi/tatooine_valariangang_medium.iff","object/building/poi/tatooine_valariantrader_medium.iff"},
	buildingsHard = {"object/building/poi/tatooine_valariangang_medium.iff","object/building/poi/tatooine_valariantrader_medium.iff"},
	buildingsVeryHard = {"object/building/poi/tatooine_valariangang_medium.iff","object/building/poi/tatooine_valariantrader_medium.iff"},
	missionBuilding = "object/tangible/lair/base/objective_power_transformer.iff",
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("tatooine_valarian_camp", tatooine_valarian_camp)
