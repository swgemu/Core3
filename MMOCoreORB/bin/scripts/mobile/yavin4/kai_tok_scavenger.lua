kai_tok_scavenger = Creature:new {
	objectName = "@mob/creature_names:kai_tok_scavenger",
	socialGroup = "kai_tok",
	faction = "",
	level = 31,
	chanceHit = 0.39,
	damageMin = 260,
	damageMax = 270,
	baseXp = 3097,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {135,130,0,0,0,-1,-1,-1,-1},
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
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kai_tok_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/kai_tok_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(kai_tok_scavenger, "kai_tok_scavenger")
