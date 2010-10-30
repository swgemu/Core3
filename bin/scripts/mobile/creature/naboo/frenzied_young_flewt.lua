frenzied_young_flewt = Creature:new {
	objectName = "frenzied young flewt",
	socialGroup = "Flewt",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 200,
	baseHAMmax = 200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 1,
	hideType = "hide_leathery",
	hideAmount = 1,
	boneType = "bone_avian",
	boneAmount = 1,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/flewt.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(frenzied_young_flewt, "frenzied_young_flewt")