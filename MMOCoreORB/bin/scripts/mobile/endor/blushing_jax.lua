blushing_jax = Creature:new {
	objectName = "@mob/creature_names:blushing_jax",
	socialGroup = "jax",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2730,
	baseHAM = 8300,
	baseHAMmax = 9900,
	armor = 0,
	resists = {135,130,150,-1,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/blushing_jax.iff"},
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(blushing_jax, "blushing_jax")
