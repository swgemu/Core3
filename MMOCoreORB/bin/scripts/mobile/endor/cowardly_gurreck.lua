cowardly_gurreck = Creature:new {
	objectName = "@mob/creature_names:cowardly_gurreck",
	socialGroup = "gurreck",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 150,
	damageMax = 160,
	baseXp = 831,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {110,110,5,-1,-1,5,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 55,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/gurreck_hue.iff",
	scale = 0.85,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(cowardly_gurreck, "cowardly_gurreck")
