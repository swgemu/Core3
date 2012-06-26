large_cave_beetle = Creature:new {
	objectName = "@mob/creature_names:large_cave_beetle",
	socialGroup = "beetle",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.35,
	damageMin = 180,
	damageMax = 190,
	baseXp = 2443,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {50,10,-1,-1,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_sand_beetle.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(large_cave_beetle, "large_cave_beetle")