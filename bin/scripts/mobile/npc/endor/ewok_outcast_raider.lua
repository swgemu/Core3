ewok_outcast_raider = Creature:new {
	objectName = "@mob/creature_names:ewok_outcast_raider",
	socialGroup = "Ewok Outcast",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.390000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {25,0,0,60,60,0,0,-1,-1},
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
	weapons = {"ewok_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(ewok_outcast_raider, "ewok_outcast_raider")