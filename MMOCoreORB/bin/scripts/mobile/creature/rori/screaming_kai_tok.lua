screaming_kai_tok = Creature:new {
	objectName = "@mob/creature_names:screaming_kai_tok",
	socialGroup = "Kai Tok",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.45,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 1,
	resists = {5,5,60,45,45,5,5,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_green"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(screaming_kai_tok, "screaming_kai_tok")