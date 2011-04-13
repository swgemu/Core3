wise_panshee_rigualist = Creature:new {
	objectName = "wise Panshee rigualist",
	socialGroup = "Panshee Tribe",
	pvpFaction = "Panshee Tribe",
	faction = "",
	level = 51,
	chanceHit = 0.500000,
	damageMin = 410,
	damageMax = 530,
	baseXp = 4916,
	baseHAM = 9900,
	baseHAMmax = 12100,
	armor = 0,
	resists = {20,20,0,60,60,60,60,-1,-1},
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

CreatureTemplates:addCreatureTemplate(wise_panshee_rigualist, "wise_panshee_rigualist")