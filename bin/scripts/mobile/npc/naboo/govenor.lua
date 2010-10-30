govenor = Creature:new {
	objectName = "govenor",
	socialGroup = "Naboo",
	pvpFaction = "Naboo",
	faction = "",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 675,
	damageMax = 825,
	baseXp = 235,
	baseHAM = 675,
	baseHAMmax = 825,
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
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(govenor, "govenor")