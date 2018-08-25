midnight_vir_vur = Creature:new {
	objectName = "@mob/creature_names:midnight_vir_vur",
	socialGroup = "vir_vur",
	faction = "",
	level = 16,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "hide_wooly",
	hideAmount = 6,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/vir_vur_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/vir_vur_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(midnight_vir_vur, "midnight_vir_vur")
