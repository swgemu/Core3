corellia_corsec_base_neutral_theater = Lair:new {
	mobiles = {{"corsec_detective",1},{"corsec_inspector_sergeant",1},{"corsec_investigator",1},{"corsec_special_agent",1}},
	spawnLimit = 15,
	buildingsVeryEasy = {"object/building/poi/corellia_corsec_large2.iff"},
	buildingsEasy = {"object/building/poi/corellia_corsec_large2.iff"},
	buildingsMedium = {"object/building/poi/corellia_corsec_large2.iff"},
	buildingsHard = {"object/building/poi/corellia_corsec_large2.iff"},
	buildingsVeryHard = {"object/building/poi/corellia_corsec_large2.iff"},
	buildingType = "theater"
}

addLairTemplate("corellia_corsec_base_neutral_theater", corellia_corsec_base_neutral_theater)
