competent_gondula_ritualist = Creature:new {
	objectName = "Competent Gondula ritualist",
	socialGroup = "Condula Tribe",
	pvpFaction = "Condula Tribe",
	faction = "",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 150,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"ewok_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(competent_gondula_ritualist, "competent_gondula_ritualist")