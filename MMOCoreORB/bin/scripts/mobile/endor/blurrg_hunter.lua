blurrg_hunter = Creature:new {
	objectName = "@mob/creature_names:blurrg_hunter",
	socialGroup = "blurrg",
	faction = "",
	level = 20,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {115,120,5,135,135,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 50,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 0.85,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"knockdownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(blurrg_hunter, "blurrg_hunter")
