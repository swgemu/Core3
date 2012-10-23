majestic_plumed_rasp = Creature:new {
	objectName = "@mob/creature_names:majestic_plumed_rasp",
	socialGroup = "rasp",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 160,
	damageMax = 170,
	baseXp = 514,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,10,0,-1,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/plumed_rasp_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(majestic_plumed_rasp, "majestic_plumed_rasp")