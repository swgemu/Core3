frenzied_marauder = Creature:new {
	objectName = "@mob/creature_names:frenzied_marauder",
	socialGroup = "Marauder",
	pvpFaction = "Marauder",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 470,
	damageMax = 650,
	baseXp = 4916,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 0,
	resists = {40,40,0,-1,-1,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(frenzied_marauder, "frenzied_marauder")