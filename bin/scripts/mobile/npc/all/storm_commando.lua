storm_commando = Creature:new {
	objectName = "@mob/creature_names:storm_commando",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 29,
	chanceHit = 0.380000,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3005,
	baseHAM = 6100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {0,0,0,30,-1,30,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"stormtrooper_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(storm_commando, "storm_commando")