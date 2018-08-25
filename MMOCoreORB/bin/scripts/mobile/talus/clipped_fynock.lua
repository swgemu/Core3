clipped_fynock = Creature:new {
	objectName = "@mob/creature_names:clipped_fynock",
	socialGroup = "fynock",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 850,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 20,
	hideType = "hide_leathery",
	hideAmount = 30,
	boneType = "bone_avian",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/clipped_fynock.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(clipped_fynock, "clipped_fynock")
