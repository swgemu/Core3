sennex_hunter = Creature:new {
	objectName = "@mob/creature_names:sennex_hunter",
	socialGroup = "Sennex",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.370000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2914,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {0,0,0,30,-1,30,-1,-1,-1},
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
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(sennex_hunter, "sennex_hunter")