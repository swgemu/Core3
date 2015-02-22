female_razor_cat = Creature:new {
	objectName = "@mob/creature_names:female_sand_panther",
	socialGroup = "panther",
	faction = "",
	level = 22,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2219,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {10,10,10,160,10,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 7,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_sand_panther_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/corellian_sand_panther_hue.iff",
	scale = 0.95,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_razor_cat, "female_razor_cat")
