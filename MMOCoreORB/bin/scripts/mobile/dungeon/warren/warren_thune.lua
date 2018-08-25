warren_thune = Creature:new {
	objectName = "@mob/creature_names:warren_thune",
	socialGroup = "warren_huurton",
	faction = "",
	level = 26,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {120,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 115,
	hideType = "hide_wooly",
	hideAmount = 125,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/thune_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(warren_thune, "warren_thune")
