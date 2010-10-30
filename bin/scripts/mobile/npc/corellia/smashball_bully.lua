smashball_bully = Creature:new {
	objectName = "@mob/creature_names:smashball_bully",
	socialGroup = "Smashball",
	pvpFaction = "Smashball",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 180,
	baseHAMmax = 220,
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(smashball_bully, "smashball_bully")