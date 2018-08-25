blurrg_tracker = Creature:new {
	objectName = "@mob/creature_names:blurrg_tracker",
	socialGroup = "blurrg",
	faction = "",
	level = 28,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {125,125,15,140,180,15,-1,-1,-1},
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
	scale = 0.95,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"knockdownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(blurrg_tracker, "blurrg_tracker")
