giant_spined_snake = Creature:new {
	objectName = "@mob/creature_names:giant_spined_snake",
	socialGroup = "Spinesnake",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.34,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2219,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {10,10,50,50,50,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 8,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_spined_snake.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_spined_snake, "giant_spined_snake")