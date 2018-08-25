sandy_spined_snake = Creature:new {
	objectName = "@mob/creature_names:sandy_spined_snake",
	socialGroup = "spine_snake",
	faction = "",
	level = 13,
	chanceHit = 0.3,
	damageMin = 160,
	damageMax = 170,
	baseXp = 714,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 8,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/spined_snake_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/spined_snake_hue.iff",
	scale = 0.9,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(sandy_spined_snake, "sandy_spined_snake")
