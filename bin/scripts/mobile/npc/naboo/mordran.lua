mordran = Creature:new {
	objectName = "@mob/creature_names:mordran",
	socialGroup = "Borvo",
	pvpFaction = "Borvo",
	faction = "",
	level = 78,
	chanceHit = 0.750000,
	damageMin = 520,
	damageMax = 750,
	baseXp = 7484,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {0,75,0,45,80,0,0,0,-1},
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
	weapons = {"mordran's_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mordran, "mordran")