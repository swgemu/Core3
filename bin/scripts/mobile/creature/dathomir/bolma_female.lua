bolma_female = Creature:new {
	objectName = "bolma female",
	socialGroup = "Bolma",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2637,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {35,30,0,0,-1,-1,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 300,
	hideType = "hide_leathery",
	hideAmount = 320,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/bolma.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(bolma_female, "bolma_female")