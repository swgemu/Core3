nyms_guard = Creature:new {
	objectName = "Nym's guard",
	socialGroup = "Nym",
	pvpFaction = "Nym",
	faction = "",
	level = 36,
	chanceHit = 0.410000,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3642,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {35,35,0,0,40,-1,-1,-1,-1},
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
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(nyms_guard, "nyms_guard")