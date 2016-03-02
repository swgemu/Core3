vine_rawl = Creature:new {
	objectName = "@mob/creature_names:vine_rawl",
	socialGroup = "self",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1609,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {110,110,5,5,5,5,145,5,-1},
	meatType = "meat_reptilian",
	meatAmount = 40,
	hideType = "hide_scaley",
	hideAmount = 30,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 3,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/fanned_rawl.iff"},
	controlDeviceTemplate = "object/intangible/pet/fanned_rawl_hue.iff",
	scale = 1.3,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(vine_rawl, "vine_rawl")
