swamp_rat = Creature:new {
	objectName = "@mob/creature_names:swamp_rat",
	socialGroup = "self",
	pvpFaction = "self",
	faction = "",
	level = 10,
	chanceHit = 0.270000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 430,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,10,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/dressed_swamp_rat.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(swamp_rat, "swamp_rat")