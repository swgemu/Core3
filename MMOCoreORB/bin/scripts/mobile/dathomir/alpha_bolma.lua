alpha_bolma = Creature:new {
	objectName = "@mob/creature_names:alpha_bolma",
	socialGroup = "bolma",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.4,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3279,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {45,25,20,-1,20,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 550,
	boneType = "bone_mammal",
	boneAmount = 500,
	milk = 0,
	tamingChance = 0,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/alpha_bolma.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(alpha_bolma, "alpha_bolma")