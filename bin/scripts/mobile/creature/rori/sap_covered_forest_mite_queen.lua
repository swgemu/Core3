sap_covered_forest_mite_queen = Creature:new {
	objectName = "@mob/creature_names:sap_covered_forest_mite_queen",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {20,0,-1,-1,0,40,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/forest_mite.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sap_covered_forest_mite_queen, "sap_covered_forest_mite_queen")