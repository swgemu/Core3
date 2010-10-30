elite_novatrooper_commander = Creature:new {
	objectName = "Elite Novatrooper Commander",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 201,
	chanceHit = 16.000000,
	damageMin = 1145,
	damageMax = 2000,
	baseXp = 19104,
	baseHAM = 160000,
	baseHAMmax = 195000,
	armor = 0,
	resists = {60,75,80,30,0,0,30,45,-1},
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
	weapons = {"stormtrooper_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(elite_novatrooper_commander, "elite_novatrooper_commander")