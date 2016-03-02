spitting_rawl = Creature:new {
	objectName = "@mob/creature_names:spitting_rawl",
	socialGroup = "self",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2543,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {10,130,10,-1,-1,-1,200,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/fanned_rawl.iff"},
	controlDeviceTemplate = "object/intangible/pet/fanned_rawl_hue.iff",
	scale = 1.4,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(spitting_rawl, "spitting_rawl")
