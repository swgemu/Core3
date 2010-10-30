giant_spined_snake = Creature:new {
	objectName = "@mob/creature_names:giant_spined_snake",
	socialGroup = "Spinesnake",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.340000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2219,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {0,0,50,50,50,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 8,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_spined_snake.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_spined_snake, "giant_spined_snake")