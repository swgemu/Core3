reptilian_flier = Creature:new {
	objectName = "@mob/creature_names:reptilian_flier",
	socialGroup = "reptilian_flier",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {105,5,105,5,5,-1,5,-1,-1},
	meatType = "meat_avian",
	meatAmount = 125,
	hideType = "hide_leathery",
	hideAmount = 80,
	boneType = "bone_avian",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/reptilian_flier_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/pet_control.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(reptilian_flier, "reptilian_flier")
