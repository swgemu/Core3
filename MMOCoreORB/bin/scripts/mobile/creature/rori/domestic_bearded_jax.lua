domestic_bearded_jax = Creature:new {
	objectName = "@mob/creature_names:domestic_bearded_jax",
	socialGroup = "Narmle",
	pvpFaction = "",
	faction = "",
	level = 5,
	chanceHit = 0.25,
	damageMin = 45,
	damageMax = 50,
	baseXp = 85,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 11,
	hideType = "hide_bristley",
	hideAmount = 16,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bearded_jax.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(domestic_bearded_jax, "domestic_bearded_jax")