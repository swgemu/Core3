blight_boar = Creature:new {
	objectName = "@mob/creature_names:zucca_boar_blight",
	socialGroup = "boar",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 150,
	damageMax = 160,
	baseXp = 514,
	baseHAM = 1100,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 65,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/zucca_boar.iff"},
	controlDeviceTemplate = "object/intangible/pet/zucca_boar_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blight_boar, "blight_boar")
