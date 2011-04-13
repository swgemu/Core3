rebel_ensign = Creature:new {
	objectName = "Rebel Ensign",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 72,
	chanceHit = 0.700000,
	damageMin = 495,
	damageMax = 700,
	baseXp = 6931,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {45,35,0,0,30,30,80,65,-1},
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

CreatureTemplates:addCreatureTemplate(rebel_ensign, "rebel_ensign")