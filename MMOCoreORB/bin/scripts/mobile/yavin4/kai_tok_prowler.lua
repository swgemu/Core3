kai_tok_prowler = Creature:new {
	objectName = "@mob/creature_names:kai_tok_prowler",
	socialGroup = "kai_tok",
	faction = "",
	level = 26,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {130,120,0,0,-1,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 55,
	hideType = "hide_leathery",
	hideAmount = 41,
	boneType = "bone_avian",
	boneAmount = 46,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/kai_tok_hue.iff",
	scale = 0.9,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(kai_tok_prowler, "kai_tok_prowler")
