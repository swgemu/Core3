nyms_elite_pirate = Creature:new {
	objectName = "Nym's elite pirate",
	socialGroup = "Nym",
	pvpFaction = "Nym",
	faction = "",
	level = 31,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3188,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {0,40,0,0,40,-1,-1,-1,-1},
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
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(nyms_elite_pirate, "nyms_elite_pirate")