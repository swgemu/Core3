masterful_jinda_warrior = Creature:new {
	objectName = "@mob/creature_names:masterful_jinda_warrior",
	socialGroup = "Jinda Tribe",
	pvpFaction = "Jinda Tribe",
	faction = "",
	level = 42,
	chanceHit = 0.440000,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4188,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {40,40,0,0,0,0,0,0,-1},
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
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(masterful_jinda_warrior, "masterful_jinda_warrior")