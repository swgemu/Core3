festering_dung_mite_queen = Creature:new {
	objectName = "@mob/creature_names:festering_dung_queen",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1426,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {15,5,0,-1,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 13,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/dung_mite.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(festering_dung_mite_queen, "festering_dung_mite_queen")