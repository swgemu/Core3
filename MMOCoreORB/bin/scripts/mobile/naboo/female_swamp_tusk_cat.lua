female_swamp_tusk_cat = Creature:new {
	objectName = "@mob/creature_names:female_swamp_tusk_cat",
	socialGroup = "tusk_cat",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {5,5,5,-1,130,-1,135,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/female_swamp_tusk_cat.iff"},
	controlDeviceTemplate = "object/intangible/pet/tusk_cat_hue.iff",
	scale = 0.95,
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(female_swamp_tusk_cat, "female_swamp_tusk_cat")
