dark_jedi_knight = Creature:new {
	objectName = "@mob/creature_names:dark_jedi_knight",
	socialGroup = "Dark Jedi",
	pvpFaction = "",
	faction = "",
	level = 265,
	chanceHit = 23.500000,
	damageMin = 1645,
	damageMax = 3000,
	baseXp = 25266,
	baseHAM = 261000,
	baseHAMmax = 320000,
	armor = 0,
	resists = {90,90,90,90,90,90,90,90,-1},
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
	creatureBitmask = KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"dark_jedi_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(dark_jedi_knight, "dark_jedi_knight")