afarathu_savage = Creature:new {
	objectName = "Afarathu savage",
	socialGroup = "Afarathu",
	pvpFaction = "Afarathu",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 180,
	baseHAMmax = 220,
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
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(afarathu_savage, "afarathu_savage")