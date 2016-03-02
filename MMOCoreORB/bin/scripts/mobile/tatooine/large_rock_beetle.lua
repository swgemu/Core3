large_rock_beetle = Creature:new {
	objectName = "@mob/creature_names:large_rock_beetle",
	socialGroup = "beetle",
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 170,
	damageMax = 180,
	baseXp = 2006,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {120,120,5,115,5,-1,5,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_sand_beetle.iff"},
	controlDeviceTemplate = "object/intangible/pet/rock_mite_hue.iff",
	scale = 1.5,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(large_rock_beetle, "large_rock_beetle")
