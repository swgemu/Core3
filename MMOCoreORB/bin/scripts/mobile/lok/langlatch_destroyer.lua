langlatch_destroyer = Creature:new {
	objectName = "@mob/creature_names:langlatch_destroyer",
	socialGroup = "langlatch",
	faction = "",
	level = 20,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {120,0,0,115,115,145,145,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 18,
	hideType = "hide_wooly",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/langlatch_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/langlatch_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"knockdownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(langlatch_destroyer, "langlatch_destroyer")
