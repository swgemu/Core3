hunter = Creature:new {
	objectName = "@mob/creature_names:hunter",
	socialGroup = "poacher",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_commoner_tatooine_devaronian_male_03.iff",
		"object/mobile/dressed_commoner_naboo_twilek_male_01.iff",
		"object/mobile/dressed_commoner_naboo_moncal_male_01.iff"},
	lootGroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(hunter, "hunter")