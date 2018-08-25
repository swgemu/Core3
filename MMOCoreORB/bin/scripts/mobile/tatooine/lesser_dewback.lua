lesser_dewback = Creature:new {
	objectName = "@mob/creature_names:lesser_dewback",
	socialGroup = "dewback",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 50,
	damageMax = 55,
	baseXp = 292,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {115,0,110,0,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 175,
	hideType = "hide_leathery",
	hideAmount = 125,
	boneType = "bone_mammal",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/dewback_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/dewback_hue.iff",
	scale = 0.8,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(lesser_dewback, "lesser_dewback")
