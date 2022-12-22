corellia_afarathu_cult_outpost_neutral_medium_theater = Lair:new {
	mobiles = {{"afarathu_hellion",2},{"afarathu_cult_bodyguard",2},{"afarathu_cult_leader",1}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_afarathu_small1.iff","object/building/poi/corellia_afarathu_small2.iff","object/building/poi/corellia_afarathu_small3.iff"},
	buildingsEasy = {"object/building/poi/corellia_afarathu_small1.iff","object/building/poi/corellia_afarathu_small2.iff","object/building/poi/corellia_afarathu_small3.iff"},
	buildingsMedium = {"object/building/poi/corellia_afarathu_medium2.iff"},
	buildingsHard = {"object/building/poi/corellia_afarathu_large1.iff","object/building/poi/corellia_afarathu_large2.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_afarathu_large1.iff","object/building/poi/corellia_afarathu_large2.iff"},
	mobType = "npc",
	buildingType = "theater"
}

addLairTemplate("corellia_afarathu_cult_outpost_neutral_medium_theater", corellia_afarathu_cult_outpost_neutral_medium_theater)
