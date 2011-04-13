scientist = Creature:new {
	objectName = "@mob/creature_names:scientist",
	socialGroup = "Warren Teraud",
	pvpFaction = "Warren Teraud",
	faction = "",
	level = 36,
	chanceHit = 0.420000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3460,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(scientist, "scientist")