craggy_bolma = Creature:new {
	objectName = "@mob/creature_names:craggy_bolma",
	socialGroup = "Bolma",
	pvpFaction = "",
	faction = "",
	level = 47,
	chanceHit = 0.47,
	damageMin = 375,
	damageMax = 460,
	baseXp = 4643,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {25,40,0,0,-1,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 550,
	boneType = "bone_mammal",
	boneAmount = 500,
	milk = 0,
	tamingChance = 0.15,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bolma.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(craggy_bolma, "craggy_bolma")