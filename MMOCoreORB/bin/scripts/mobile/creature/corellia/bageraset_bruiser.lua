bageraset_bruiser = Creature:new {
	objectName = "@mob/creature_names:bageraset_bruiser",
	socialGroup = "Bageraset",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 230,
	hideType = "hide_leathery",
	hideAmount = 130,
	boneType = "bone_mammal",
	boneAmount = 80,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bageraset.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bageraset_bruiser, "bageraset_bruiser")