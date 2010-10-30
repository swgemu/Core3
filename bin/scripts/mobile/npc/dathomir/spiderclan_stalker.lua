spiderclan_stalker = Creature:new {
	objectName = "Spiderclan stalker",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "Sp. Nightsister",
	faction = "",
	level = 100,
	chanceHit = 0.850000,
	damageMin = 620,
	damageMax = 950,
	baseXp = 9522,
	baseHAM = 20000,
	baseHAMmax = 25000,
	armor = 0,
	resists = {90,100,100,0,100,100,0,0,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(spiderclan_stalker, "spiderclan_stalker")