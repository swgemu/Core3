korga_ancient = Creature:new {
	objectName = "@mob/creature_names:korga_ancient",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 47,
	chanceHit = 0.480000,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4643,
	baseHAM = 9800,
	baseHAMmax = 12000,
	armor = 0,
	resists = {25,15,0,50,50,-1,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(korga_ancient, "korga_ancient")