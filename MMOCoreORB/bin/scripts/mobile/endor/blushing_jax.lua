blushing_jax = Creature:new {
	objectName = "@mob/creature_names:blushing_jax",
	socialGroup = "jax",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2730,
	baseHAM = 8300,
	baseHAMmax = 9900,
	armor = 0,
	resists = {35,30,50,-1,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/blushing_jax.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blushing_jax, "blushing_jax")