grecks_assassin = Creature:new {
	objectName = "Greck's assassin",
	socialGroup = "Olag Greck",
	pvpFaction = "Olag Greck",
	faction = "",
	level = 11,
	chanceHit = 0.290000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 514,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"ranged_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(grecks_assassin, "grecks_assassin")