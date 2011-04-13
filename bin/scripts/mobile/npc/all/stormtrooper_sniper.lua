stormtrooper_sniper = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_sniper",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
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
	weapons = {"st_sniper_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(stormtrooper_sniper, "stormtrooper_sniper")