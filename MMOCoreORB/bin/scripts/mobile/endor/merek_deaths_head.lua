merek_deaths_head = Creature:new {
	objectName = "@mob/creature_names:merek_deaths_head",
	socialGroup = "merek",
	faction = "",
	level = 56,
	chanceHit = 0.55,
	damageMin = 480,
	damageMax = 670,
	baseXp = 5464,
	baseHAM = 9900,
	baseHAMmax = 12100,
	armor = 1,
	resists = {10,10,10,10,10,10,10,10,-1},
	meatType = "meat_wild",
	meatAmount = 64,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/merek_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/merek_hue.iff",
	scale = 1.3,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(merek_deaths_head, "merek_deaths_head")
