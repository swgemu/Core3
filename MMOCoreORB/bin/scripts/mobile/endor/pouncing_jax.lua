pouncing_jax = Creature:new {
	objectName = "@mob/creature_names:pouncing_jax",
	socialGroup = "jax",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 150,
	damageMax = 160,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,110,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bearded_jax.iff"},
	controlDeviceTemplate = "object/intangible/pet/bearded_jax_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(pouncing_jax, "pouncing_jax")
