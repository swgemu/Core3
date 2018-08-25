merek_cavern_creeper = Creature:new {
	objectName = "@mob/creature_names:merek_cavern_creeper",
	socialGroup = "merek",
	faction = "",
	level = 40,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3915,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {140,30,30,30,-1,30,30,30,-1},
	meatType = "meat_wild",
	meatAmount = 64,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/merek_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	controlDeviceTemplate = "object/intangible/pet/merek_hue.iff",
	scale = 0.95,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(merek_cavern_creeper, "merek_cavern_creeper")
