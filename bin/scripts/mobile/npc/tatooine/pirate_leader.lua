pirate_leader = Creature:new {
	objectName = "@mob/creature_names:pirate_leader",
	socialGroup = "Pirate",
	pvpFaction = "",
	faction = "",
	level = 43,
	chanceHit = 0.460000,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4279,
	baseHAM = 8600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {10,15,0,40,-1,40,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(pirate_leader, "pirate_leader")