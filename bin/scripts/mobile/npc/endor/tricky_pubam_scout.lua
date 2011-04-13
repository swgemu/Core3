tricky_pubam_scout = Creature:new {
	objectName = "@mob/creature_names:tricky_pubam_scout",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 50,
	chanceHit = 0.550000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {-1,35,0,0,0,-1,0,0,-1},
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
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(tricky_pubam_scout, "tricky_pubam_scout")