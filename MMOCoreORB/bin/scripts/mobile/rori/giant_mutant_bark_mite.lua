giant_mutant_bark_mite = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_giant",
	socialGroup = "mite",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {5,5,5,110,110,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 30,
	hideType = "hide_scaley",
	hideAmount = 25,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	controlDeviceTemplate = "object/intangible/pet/bark_mite_hue.iff",
	scale = 3,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_mutant_bark_mite, "giant_mutant_bark_mite")
