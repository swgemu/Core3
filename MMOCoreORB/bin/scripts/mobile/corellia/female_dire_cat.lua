female_dire_cat = Creature:new {
	objectName = "@mob/creature_names:female_dire_cat",
	socialGroup = "dire_cat",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 120,
	damageMax = 130,
	baseXp = 430,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,115,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/female_dire_cat.iff"},
	controlDeviceTemplate = "object/intangible/pet/narglatch_hue.iff",
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_dire_cat, "female_dire_cat")
