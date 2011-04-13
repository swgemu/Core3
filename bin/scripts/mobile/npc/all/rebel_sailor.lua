rebel_sailor = Creature:new {
	objectName = "Rebel Sailor",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 96,
	chanceHit = 0.950000,
	damageMin = 620,
	damageMax = 950,
	baseXp = 9150,
	baseHAM = 20000,
	baseHAMmax = 25000,
	armor = 0,
	resists = {45,45,0,0,30,30,80,65,-1},
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
	weapons = {"rebel_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rebel_sailor, "rebel_sailor")