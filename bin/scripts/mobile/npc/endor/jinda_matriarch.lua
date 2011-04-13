jinda_matriarch = Creature:new {
	objectName = "@mob/creature_names:jinda_matriarch",
	socialGroup = "Jinda Tribe",
	pvpFaction = "Jinda Tribe",
	faction = "",
	level = 41,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4006,
	baseHAM = 10000,
	baseHAMmax = 12200,
	armor = 0,
	resists = {0,0,-1,0,0,60,0,-1,-1},
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
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(jinda_matriarch, "jinda_matriarch")