spiderclan_web_dancer = Creature:new {
	objectName = "Spiderclan web dancer",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "Sp. Nightsister",
	faction = "",
	level = 87,
	chanceHit = 0.750000,
	damageMin = 520,
	damageMax = 750,
	baseXp = 8315,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {100,95,100,65,100,0,90,100,-1},
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

CreatureTemplates:addCreatureTemplate(spiderclan_web_dancer, "spiderclan_web_dancer")