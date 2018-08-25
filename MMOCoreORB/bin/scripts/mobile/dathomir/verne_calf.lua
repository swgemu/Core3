verne_calf = Creature:new {
	objectName = "@mob/creature_names:verne_calf",
	socialGroup = "verne",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 130,
	damageMax = 140,
	baseXp = 714,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 18,
	hideType = "hide_leathery",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 12,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/verne_calf.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 0.85,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(verne_calf, "verne_calf")
