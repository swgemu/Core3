festering_dung_mite_queen = Creature:new {
	objectName = "@mob/creature_names:festering_dung_queen",
	socialGroup = "mite",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1426,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {115,105,0,-1,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 13,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/dung_mite.iff"},
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(festering_dung_mite_queen, "festering_dung_mite_queen")
