korga_dark_shaman = Creature:new {
	objectName = "@mob/creature_names:korga_dark_shaman",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 46,
	chanceHit = 0.470000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4552,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {35,20,0,50,50,-1,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(korga_dark_shaman, "korga_dark_shaman")