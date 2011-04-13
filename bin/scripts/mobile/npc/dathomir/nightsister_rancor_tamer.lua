nightsister_rancor_tamer = Creature:new {
	objectName = "@mob/creature_names:nightsister_rancor_tamer",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 76,
	chanceHit = 0.750000,
	damageMin = 520,
	damageMax = 750,
	baseXp = 7299,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {0,0,0,50,50,50,50,100,-1},
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
	weapons = {"mixed_force_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(nightsister_rancor_tamer, "nightsister_rancor_tamer")