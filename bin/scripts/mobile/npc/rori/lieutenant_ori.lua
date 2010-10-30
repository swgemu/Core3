lieutenant_ori = Creature:new {
	objectName = "@mob/creature_names:lieutenant_ori",
	socialGroup = "Rorgungan",
	pvpFaction = "Rorgungan",
	faction = "",
	level = 33,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3370,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {45,45,-1,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"lt._ori's_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(lieutenant_ori, "lieutenant_ori")