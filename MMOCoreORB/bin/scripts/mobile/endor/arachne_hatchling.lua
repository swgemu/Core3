arachne_hatchling = Creature:new {
	objectName = "@mob/creature_names:arachne_hatchling",
	socialGroup = "arachne",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {110,110,5,-1,-1,5,185,5,-1},
	meatType = "meat_insect",
	meatAmount = 1,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/arachne_hatchling.iff"},
	scale = 0.75,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_hatchling, "arachne_hatchling")
