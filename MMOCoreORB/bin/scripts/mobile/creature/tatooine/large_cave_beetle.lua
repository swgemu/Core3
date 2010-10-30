large_cave_beetle = Creature:new {
	objectName = "@mob/creature_names:large_cave_beetle",
	socialGroup = "Rock Beetle",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.350000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 2443,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {50,0,-1,-1,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/rock_beetle.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(large_cave_beetle, "large_cave_beetle")