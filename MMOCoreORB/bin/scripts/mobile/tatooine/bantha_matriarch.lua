bantha_matriarch = Creature:new {
	objectName = "@mob/creature_names:matriarch_bantha",
	socialGroup = "bantha",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 7700,
	baseHAMmax = 8550,
	armor = 0,
	resists = {135,110,10,150,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 485,
	hideType = "hide_wooly",
	hideAmount = 365,
	boneType = "bone_mammal",
	boneAmount = 320,
	milkType = "milk_wild",
	milk = 265,
	tamingChance = 0,
	ferocity = 4,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/matriarch_bantha.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(bantha_matriarch, "bantha_matriarch")
