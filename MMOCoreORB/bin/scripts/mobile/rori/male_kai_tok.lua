male_kai_tok = Creature:new {
	objectName = "@mob/creature_names:male_kai_tok",
	socialGroup = "kai_tok",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {115,105,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok.iff"},
	controlDeviceTemplate = "object/intangible/pet/kai_tok_hue.iff",
	lootGroups = {},
	weapons = {"creature_spit_small_green"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(male_kai_tok, "male_kai_tok")
