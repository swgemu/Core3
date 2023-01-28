imperial_listening_post = Lair:new {
	mobiles = {
		{"imperial_warrant_officer_i",1},
		{"imperial_warrant_officer_ii",1}
	},
	spawnLimit = 12,
	buildingsVeryEasy = {"object/building/poi/imperial_listening_post.iff"},
	buildingsEasy = {"object/building/poi/imperial_listening_post.iff"},
	buildingsMedium = {"object/building/poi/imperial_listening_post.iff"},
	buildingsHard = {"object/building/poi/imperial_listening_post.iff"},
	buildingsVeryHard = {"object/building/poi/imperial_listening_post.iff"},
	missionBuilding = "object/tangible/lair/base/objective_banner_imperial.iff",
	mobType = "npc",
	buildingType = "theater",
	faction = "imperial"
}

addLairTemplate("imperial_listening_post", imperial_listening_post)
