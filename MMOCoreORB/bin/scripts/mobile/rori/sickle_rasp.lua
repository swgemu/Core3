sickle_rasp = Creature:new {
	objectName = "@mob/creature_names:sickle_rasp",
	socialGroup = "rasp",
	faction = "",
	level = 8,
	chanceHit = 0.27,
	damageMin = 90,
	damageMax = 110,
	baseXp = 235,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,110,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 15,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/crowned_rasp_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mildpoison",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(sickle_rasp, "sickle_rasp")
