puny_tanc_mite = Creature:new {
	objectName = "@mob/creature_names:puny_tanc_mite",
	socialGroup = "mite",
	faction = "",
	level = 2,
	chanceHit = 0.21,
	damageMin = 35,
	damageMax = 40,
	baseXp = 45,
	baseHAM = 68,
	baseHAMmax = 83,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 2,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/puny_tanc_mite.iff"},
	controlDeviceTemplate = "object/intangible/pet/tanc_mite_hue.iff",
	scale = 0.6,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(puny_tanc_mite, "puny_tanc_mite")
