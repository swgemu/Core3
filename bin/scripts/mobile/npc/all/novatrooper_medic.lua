novatrooper_medic = Creature:new {
	objectName = "Novatrooper Medic",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 107,
	chanceHit = 1.750000,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 10174,
	baseHAM = 29000,
	baseHAMmax = 36000,
	armor = 0,
	resists = {40,35,80,30,0,0,30,45,-1},
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
	weapons = {"stormtrooper_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(novatrooper_medic, "novatrooper_medic")