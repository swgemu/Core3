screaming_kai_tok = Creature:new {
	objectName = "@mob/creature_names:screaming_kai_tok",
	socialGroup = "kai_tok",
	faction = "",
	level = 21,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {120,110,135,145,145,5,5,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/kai_tok_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {"creature_spit_small_green"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(screaming_kai_tok, "screaming_kai_tok")
