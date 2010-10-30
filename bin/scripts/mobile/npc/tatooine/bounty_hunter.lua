bounty_hunter = Creature:new {
	objectName = "@mob/creature_names:bounty_hunter",
	socialGroup = "Townsperson",
	pvpFaction = "Townsperson",
	faction = "",
	level = 99,
	chanceHit = 1.000000,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9243,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(bounty_hunter, "bounty_hunter")