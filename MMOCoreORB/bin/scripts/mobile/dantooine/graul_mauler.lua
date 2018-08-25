graul_mauler = Creature:new {
	objectName = "@mob/creature_names:graul_mauler",
	socialGroup = "graul",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3551,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {145,20,160,160,160,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 875,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/graul_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/graul_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(graul_mauler, "graul_mauler")
