spiderclan_sentinel = Creature:new {
	objectName = "Spiderclan sentinel",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "Sp. Nightsister",
	faction = "",
	level = 92,
	chanceHit = 0.800000,
	damageMin = 545,
	damageMax = 800,
	baseXp = 8778,
	baseHAM = 21000,
	baseHAMmax = 26000,
	armor = 0,
	resists = {55,100,45,60,100,100,0,100,-1},
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

CreatureTemplates:addCreatureTemplate(spiderclan_sentinel, "spiderclan_sentinel")