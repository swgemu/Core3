plumed_rasp = Creature:new {
	objectName = "@mob/creature_names:plumed_rasp",
	socialGroup = "rasp",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 80,
	damageMax = 90,
	baseXp = 147,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {0,0,0,0,0,115,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 3,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/plumed_rasp_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/plumed_rasp_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(plumed_rasp, "plumed_rasp")
