majestic_plumed_rasp = Creature:new {
	objectName = "@mob/creature_names:majestic_plumed_rasp",
	socialGroup = "rasp",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 160,
	damageMax = 170,
	baseXp = 514,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,110,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 5,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/plumed_rasp_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(majestic_plumed_rasp, "majestic_plumed_rasp")
