huurton_howler = Creature:new {
	objectName = "@mob/creature_names:huurton_howler",
	socialGroup = "huurton",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {115,115,10,140,160,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 15,
	hideType = "hide_wooly",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/huurton_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(huurton_howler, "huurton_howler")
