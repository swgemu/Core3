fuzzy_jax = Creature:new {
	objectName = "@mob/creature_names:fuzzy_jax",
	socialGroup = "jax",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 140,
	damageMax = 150,
	baseXp = 514,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {110,125,110,-1,0,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 11,
	hideType = "hide_bristley",
	hideAmount = 16,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bearded_jax_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/bearded_jax_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(fuzzy_jax, "fuzzy_jax")
