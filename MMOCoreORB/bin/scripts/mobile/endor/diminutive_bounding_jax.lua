diminutive_bounding_jax = Creature:new {
	objectName = "@mob/creature_names:jax_bounding_dwarf",
	socialGroup = "jax",
	faction = "",
	level = 7,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 187,
	baseHAM = 68,
	baseHAMmax = 83,
	armor = 0,
	resists = {110,110,-1,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bearded_jax_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/bearded_jax_hue.iff",
	scale = 0.75,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(diminutive_bounding_jax, "diminutive_bounding_jax")
