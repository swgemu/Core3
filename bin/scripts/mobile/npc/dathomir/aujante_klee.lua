aujante_klee = Creature:new {
	objectName = "@mob/creature_names:aujante_klee",
	socialGroup = "Mtn. Clan",
	pvpFaction = "Mtn. Clan",
	faction = "",
	level = 23,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {25,25,0,40,40,40,40,-1,-1},
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(aujante_klee, "aujante_klee")