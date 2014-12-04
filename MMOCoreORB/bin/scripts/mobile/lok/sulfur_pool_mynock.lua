sulfur_pool_mynock = Creature:new {
	objectName = "@mob/creature_names:sulfur_pool_mynock",
	socialGroup = "mynock",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {-1,150,20,200,-1,20,200,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 57,
	hideType = "hide_leathery",
	hideAmount = 75,
	boneType = "bone_mammal",
	boneAmount = 27,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/riverside_sulfur_mynock.iff"},
	controlDeviceTemplate = "object/intangible/pet/salt_mynock_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sulfur_pool_mynock, "sulfur_pool_mynock")
