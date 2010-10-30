escaped_nightsister_slave = Creature:new {
	objectName = "@mob/creature_names:escaped_nightsister_slave",
	socialGroup = "Escaped Slave",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.360000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2730,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {35,35,0,-1,-1,-1,-1,0,-1},
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(escaped_nightsister_slave, "escaped_nightsister_slave")