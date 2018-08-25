deadly_vesp = Creature:new {
	objectName = "@mob/creature_names:deadly_vesp",
	socialGroup = "vesp",
	faction = "",
	level = 93,
	chanceHit = 0.9,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 8871,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 0,
	resists = {140,140,0,0,0,0,0,0,-1},
	meatType = "meat_reptilian",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 6,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/vesp_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.35,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(deadly_vesp, "deadly_vesp")
