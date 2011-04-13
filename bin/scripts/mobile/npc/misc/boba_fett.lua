boba_fett = Creature:new {
	objectName = "@mob/creature_names:boba_fett",
	socialGroup = "Jabba",
	pvpFaction = "Jabba",
	faction = "",
	level = 99,
	chanceHit = 0.990000,
	damageMin = 640,
	damageMax = 990,
	baseXp = 9336,
	baseHAM = 24000,
	baseHAMmax = 29000,
	armor = 0,
	resists = {45,45,0,90,90,90,-1,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(boba_fett, "boba_fett")