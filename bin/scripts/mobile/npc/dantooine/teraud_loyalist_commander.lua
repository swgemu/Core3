teraud_loyalist_commander = Creature:new {
	objectName = "Teraud loyalist commander",
	socialGroup = "Warren Teraud",
	pvpFaction = "Warren Teraud",
	faction = "",
	level = 44,
	chanceHit = 0.470000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4370,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {0,0,0,-1,0,0,-1,0,-1},
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
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(teraud_loyalist_commander, "teraud_loyalist_commander")