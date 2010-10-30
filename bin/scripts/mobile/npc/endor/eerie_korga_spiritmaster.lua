eerie_korga_spiritmaster = Creature:new {
	objectName = "@mob/creature_names:eerie_korga_spiritmaster",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 43,
	chanceHit = 0.460000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4279,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {0,0,0,0,0,0,-1,-1,-1},
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

CreatureTemplates:addCreatureTemplate(eerie_korga_spiritmaster, "eerie_korga_spiritmaster")