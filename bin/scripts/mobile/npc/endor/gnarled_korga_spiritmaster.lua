gnarled_korga_spiritmaster = Creature:new {
	objectName = "@mob/creature_names:gnarled_korga_spiritmaster",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 33,
	chanceHit = 0.400000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3370,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {0,35,0,0,0,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(gnarled_korga_spiritmaster, "gnarled_korga_spiritmaster")