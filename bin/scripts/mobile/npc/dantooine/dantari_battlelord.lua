dantari_battlelord = Creature:new {
	objectName = "Dantari battlelord",
	socialGroup = "Dantari Raider",
	pvpFaction = "Dantari Raider",
	faction = "",
	level = 36,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3642,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,40,40,-1,60,60,-1,0,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(dantari_battlelord, "dantari_battlelord")