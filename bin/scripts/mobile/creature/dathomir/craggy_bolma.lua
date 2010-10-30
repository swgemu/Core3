craggy_bolma = Creature:new {
	objectName = "@mob/creature_names:craggy_bolma",
	socialGroup = "Bolma",
	pvpFaction = "",
	faction = "",
	level = 47,
	chanceHit = 0.470000,
	damageMin = 375,
	damageMax = 460,
	baseXp = 4643,
	baseHAM = 11500,
	baseHAMmax = 11500,
	armor = 0,
	resists = {25,40,0,0,-1,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 550,
	boneType = "bone_mammal",
	boneAmount = 500,
	milk = 0,
	tamingChance = 0.150000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/bolma.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(craggy_bolma, "craggy_bolma")