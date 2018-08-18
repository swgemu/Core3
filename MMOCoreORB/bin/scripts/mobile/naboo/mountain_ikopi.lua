mountain_ikopi = Creature:new {
	objectName = "@mob/creature_names:mountain_ikopi",
	socialGroup = "self",
	faction = "",
	level = 17,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {115,5,5,5,5,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 75,
	hideType = "hide_bristley",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0,
	ferocity = 3,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/ikopi_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_ikopi, "mountain_ikopi")
