charred_krevol = Creature:new {
	objectName = "@mob/creature_names:charred_krevol",
	socialGroup = "krevol",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,5,130,130,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 15,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/horned_krevol_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/horned_krevol_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(charred_krevol, "charred_krevol")
