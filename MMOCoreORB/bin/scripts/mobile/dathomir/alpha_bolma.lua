alpha_bolma = Creature:new {
	objectName = "@mob/creature_names:alpha_bolma",
	socialGroup = "bolma",
	faction = "",
	level = 33,
	chanceHit = 0.4,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3279,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {145,125,20,-1,20,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 550,
	boneType = "bone_mammal",
	boneAmount = 500,
	milk = 0,
	tamingChance = 0,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/alpha_bolma.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(alpha_bolma, "alpha_bolma")
