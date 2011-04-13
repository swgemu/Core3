bol_be = Creature:new {
	objectName = "bol be",
	socialGroup = "Bol",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.390000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2914,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {35,0,-1,0,0,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/bol_hue.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(bol_be, "bol_be")