mercenary_destroyer = Creature:new {
	objectName = "@mob/creature_names:mercenary_destroyer",
	socialGroup = "Lok Merc",
	pvpFaction = "Lok Merc",
	faction = "",
	level = 40,
	chanceHit = 0.430000,
	damageMin = 355,
	damageMax = 420,
	baseXp = 4006,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {60,40,0,0,0,0,-1,-1,-1},
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
	weapons = {"rebel_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mercenary_destroyer, "mercenary_destroyer")