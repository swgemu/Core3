skreeg_hunter = Creature:new {
	objectName = "@mob/creature_names:skreeg_hunter",
	socialGroup = "skreeg",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 5500,
	armor = 0,
	resists = {120,120,10,10,-1,10,10,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/skreeg_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/skreeg_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(skreeg_hunter, "skreeg_hunter")
