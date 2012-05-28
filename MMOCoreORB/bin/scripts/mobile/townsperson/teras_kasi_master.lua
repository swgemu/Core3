teras_kasi_master = Creature:new {
	objectName = "@mob/creature_names:teras_kasi_master",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 21,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {40,10,10,10,10,10,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(teras_kasi_master, "teras_kasi_master")