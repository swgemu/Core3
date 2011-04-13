vile_korga_battlelord = Creature:new {
	objectName = "@mob/creature_names:vile_korga_battlelord",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 38,
	chanceHit = 0.430000,
	damageMin = 375,
	damageMax = 460,
	baseXp = 3824,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {65,-1,0,50,50,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(vile_korga_battlelord, "vile_korga_battlelord")