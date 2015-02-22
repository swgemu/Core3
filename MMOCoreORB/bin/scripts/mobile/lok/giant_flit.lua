giant_flit = Creature:new {
	objectName = "@mob/creature_names:giant_flit",
	socialGroup = "flit",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {115,5,5,-1,5,5,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 11,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 13,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_flit.iff"},
	controlDeviceTemplate = "object/intangible/pet/flit_hue.iff",
	scale = 1.4,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_flit, "giant_flit")
