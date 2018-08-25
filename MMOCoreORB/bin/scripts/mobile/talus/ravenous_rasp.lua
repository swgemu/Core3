ravenous_rasp = Creature:new {
	objectName = "@mob/creature_names:ravenous_rasp",
	socialGroup = "rasp",
	faction = "",
	level = 31,
	chanceHit = 0.41,
	damageMin = 360,
	damageMax = 430,
	baseXp = 3188,
	baseHAM = 2400,
	baseHAMmax = 4300,
	armor = 0,
	resists = {25,25,-1,-1,25,25,25,25,-1},
	meatType = "meat_avian",
	meatAmount = 45,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/flite_rasp_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(ravenous_rasp, "ravenous_rasp")
