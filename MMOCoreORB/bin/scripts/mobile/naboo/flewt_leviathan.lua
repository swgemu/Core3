flewt_leviathan = Creature:new {
	objectName = "@mob/creature_names:flewt_leviathan",
	socialGroup = "flewt",
	faction = "",
	level = 9,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 292,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,-1,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 10,
	boneType = "bone_avian",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/flewt_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/flewt_hue.iff",
	scale = 2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(flewt_leviathan, "flewt_leviathan")
