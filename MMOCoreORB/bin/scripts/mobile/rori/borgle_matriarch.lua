borgle_matriarch = Creature:new {
	objectName = "@mob/creature_names:borgle_matriarch",
	socialGroup = "borgle",
	faction = "",
	level = 15,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 960,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {110,110,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/borgle_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(borgle_matriarch, "borgle_matriarch")
