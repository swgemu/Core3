cas_vankoo = Creature:new {
	objectName = "@mob/creature_names:cas_vankoo",
	socialGroup = "Kimogila",
	pvpFaction = "Bandit",
	faction = "",
	level = 117,
	chanceHit = 3.400000,
	damageMin = 725,
	damageMax = 1160,
	baseXp = 11109,
	baseHAM = 40000,
	baseHAMmax = 49000,
	armor = 0,
	resists = {75,75,-1,0,0,0,0,-1,-1},
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
	weapons = {"cas_vankoo's_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(cas_vankoo, "cas_vankoo")