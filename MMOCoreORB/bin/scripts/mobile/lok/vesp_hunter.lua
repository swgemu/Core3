vesp_hunter = Creature:new {
	objectName = "@mob/creature_names:vesp_hunter",
	socialGroup = "vesp",
	faction = "",
	level = 25,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2543,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {120,120,15,150,15,15,150,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 10,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/vesp_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/vesp_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(vesp_hunter, "vesp_hunter")
