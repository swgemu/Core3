choku_packmaster = Creature:new {
	objectName = "@mob/creature_names:choku_packmaster",
	socialGroup = "choku",
	faction = "",
	level = 21,
	chanceHit = 0.34,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1803,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {110,10,10,10,10,10,10,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/choku_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/choku_hue.iff",
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(choku_packmaster, "choku_packmaster")
