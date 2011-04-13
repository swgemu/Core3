eerie_donkuwah_spiritmaster = Creature:new {
	objectName = "@mob/creature_names:eerie_donkuwah_spiritmaster",
	socialGroup = "Donkuwah Tr.",
	pvpFaction = "Donkuwah Tr.",
	faction = "",
	level = 39,
	chanceHit = 0.440000,
	damageMin = 350,
	damageMax = 410,
	baseXp = 3915,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 0,
	resists = {0,0,0,-1,-1,0,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(eerie_donkuwah_spiritmaster, "eerie_donkuwah_spiritmaster")