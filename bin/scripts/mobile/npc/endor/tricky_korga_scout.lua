tricky_korga_scout = Creature:new {
	objectName = "@mob/creature_names:tricky_korga_scout",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 41,
	chanceHit = 0.450000,
	damageMin = 350,
	damageMax = 410,
	baseXp = 4097,
	baseHAM = 9400,
	baseHAMmax = 11400,
	armor = 0,
	resists = {35,0,0,75,75,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(tricky_korga_scout, "tricky_korga_scout")