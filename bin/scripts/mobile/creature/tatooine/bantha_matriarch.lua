bantha_matriarch = Creature:new {
	objectName = "bantha matriarch",
	socialGroup = "Bantha",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {35,10,0,50,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 485,
	hideType = "hide_wooly",
	hideAmount = 365,
	boneType = "bone_mammal",
	boneAmount = 320,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/matriarch_bantha.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bantha_matriarch, "bantha_matriarch")